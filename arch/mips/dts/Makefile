dtb-$(CONFIG_MACH_PISTACHIO) += pistachio_bub.dtb pistachio_marduk.dtb pistachio_beetle_mbub.dtb pistachio_concerto_mbub.dtb

targets += $(dtb-y)

# Add any required device tree compiler flags here
ifdef CONFIG_FIT
# -p for adding padding bytes in the end, this is required by mkimage to add rsa keys
DTC_FLAGS += -p 0x1000
endif

PHONY += dtbs
dtbs: $(addprefix $(obj)/, $(dtb-y))
	@:

clean-files := *.dtb
