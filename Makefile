.PHONY: upload monitor

upload: ## Build the binary
	pio run -t upload && pio device monitor -b 115200

monitor: ## Build the binary
	pio device monitor -b 115200
