PYTHON ?= python3
VENV := .venv
VENV_PYTHON := $(VENV)/bin/python
VENV_STAMP := $(VENV)/.installed
EXE := baseroms/us/SLUS_010.44

.PHONY: all setup verify split function-inventory inventory test check clean-generated

all: split

$(VENV_STAMP): requirements.txt
	$(PYTHON) -m venv $(VENV)
	$(VENV_PYTHON) -m pip install --upgrade pip
	$(VENV_PYTHON) -m pip install -r requirements.txt
	touch $(VENV_STAMP)

setup: $(VENV_STAMP)

verify:
	$(PYTHON) tools/verify_exe.py $(EXE)

split: setup verify
	$(VENV_PYTHON) -m splat split config/us/splat.yaml

function-inventory: split
	$(PYTHON) tools/inventory_functions.py asm/us/main.s build/us/function_candidates.json

inventory: verify
	@echo "usage: python3 -m btga_ps1.inventory EXTRACTED_DIR out --previews --obj"

test:
	$(PYTHON) -m unittest discover -s tests -t . -v
	$(PYTHON) mutation_check.py

check: test
	$(PYTHON) tools/check_repository.py

clean-generated:
	rm -rf asm build .splache
