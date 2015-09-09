dtb-$(CONFIG_TARGET_PISTACHIO_BUB) += pistachio_bub.dtb
dtb-$(CONFIG_TARGET_PISTACHIO_MARDUK) += pistachio_marduk.dtb
dtb-$(CONFIG_TARGET_PISTACHIO_BEETLE) += pistachio_beetle_mbub.dtb

targets += $(dtb-y)

# Add any required device tree compiler flags here
DTC_FLAGS +=

PHONY += dtbs
dtbs: $(addprefix $(obj)/, $(dtb-y))
	@:

clean-files := *.dtb
