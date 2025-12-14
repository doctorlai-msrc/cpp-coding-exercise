# ======================================
# Top-level Makefile for cpp-coding-exercise
# ======================================

# Auto-detect all subdirectories that contain a Makefile
SUBDIRS := $(dir $(wildcard */Makefile))

# Default sanitizer (can be overridden)
SANITIZE ?= address

.PHONY: all clean run $(SUBDIRS)

# --------------------------
# Build all examples
# --------------------------
all: $(SUBDIRS)

$(SUBDIRS):
	@echo "=== Building $@ with SANITIZE=$(SANITIZE) ==="
	$(MAKE) -C $@ SANITIZE=$(SANITIZE)

# --------------------------
# Run all examples (optional)
# --------------------------
run:
	@for dir in $(SUBDIRS); do \
		echo "=== Running $$dir ==="; \
		(cd $$dir && $(MAKE) SANITIZE=$(SANITIZE) run) || exit 1; \
	done

# --------------------------
# Clean all examples
# --------------------------
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
