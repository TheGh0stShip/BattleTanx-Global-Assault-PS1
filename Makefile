PYTHON ?= python3
VENV := .venv
VENV_PYTHON := $(VENV)/bin/python
VENV_STAMP := $(VENV)/.installed
EXE := baseroms/us/SLUS_010.44

.PHONY: all setup toolchain verify split function-inventory psyq-report verify-matching verify-linked inventory test check clean-generated

all: split

$(VENV_STAMP): requirements.txt
	$(PYTHON) -m venv $(VENV)
	$(VENV_PYTHON) -m pip install --upgrade pip
	$(VENV_PYTHON) -m pip install -r requirements.txt
	touch $(VENV_STAMP)

setup: $(VENV_STAMP)

toolchain:
	tools/bootstrap_toolchain.sh

verify:
	$(PYTHON) tools/verify_exe.py $(EXE)

split: setup verify
	$(VENV_PYTHON) -m splat split config/us/splat.yaml

function-inventory: split
	$(PYTHON) tools/inventory_functions.py asm/us/main.s build/us/function_candidates.json

psyq-report: function-inventory
	@test -n "$(PSYQ_SIGNATURES)" || (echo "set PSYQ_SIGNATURES to one catalogue version directory" >&2; exit 2)
	@test -n "$(PSYQ_VERSION)" || (echo "set PSYQ_VERSION to the catalogue version" >&2; exit 2)
	$(PYTHON) tools/psyq_signatures.py \
		--executable $(EXE) \
		--candidates build/us/function_candidates.json \
		--signatures "$(PSYQ_SIGNATURES)" \
		--version "$(PSYQ_VERSION)" \
		--output build/us/psyq-$(PSYQ_VERSION).json

verify-matching: verify toolchain
	$(PYTHON) tools/verify_matching_units.py

verify-linked: verify toolchain
	$(PYTHON) tools/build_matching_executable.py

inventory: verify
	@echo "usage: python3 -m btga_ps1.inventory EXTRACTED_DIR out --previews --obj"

test:
	$(PYTHON) -m unittest discover -s tests -t . -v
	$(PYTHON) mutation_check.py

check: test
	$(PYTHON) tools/check_repository.py

clean-generated:
	rm -rf asm build .splache
