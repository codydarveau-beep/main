XBE_TITLE = MyRO\ v1.11.0\ RECOVERY
GEN_XISO = MyRO-Xbox-1.11.0-RECOVERY.iso
OUTPUT_DIR = ../XboxFiles
SRCS = $(CURDIR)/main.c $(CURDIR)/ui_assets.c $(CURDIR)/loading_assets.c $(CURDIR)/sound_assets.c $(CURDIR)/skin_assets.c $(CURDIR)/pbkit_hardware54.c $(CURDIR)/frontend_assets56.c $(CURDIR)/arcade_recovered197.s
NXDK_DIR ?= $(CURDIR)/../../xbox-nxdk
NXDK_SDL = y
NXDK_CFLAGS += -O2 -fstack-usage -I$(NXDK_DIR)/lib/pbkit
# Reserve160KiB for the render loop plus nested NPC travel/save operations.
NXDK_LDFLAGS += -stack:0x28000
.DEFAULT_GOAL := all
include $(NXDK_DIR)/Makefile

all: $(OUTPUT_DIR)/world.bin
$(OUTPUT_DIR)/world.bin: $(CURDIR)/../Packed/world.bin
	cp "$<" "$@"

$(GEN_XISO): $(OUTPUT_DIR)/world.bin

all: $(OUTPUT_DIR)/actors.bin
$(OUTPUT_DIR)/actors.bin: $(CURDIR)/../Actors/actors.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/actors.bin

all: $(OUTPUT_DIR)/enemies.bin
$(OUTPUT_DIR)/enemies.bin: $(CURDIR)/../Enemies/enemies.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/enemies.bin

all: $(OUTPUT_DIR)/effects.bin
$(OUTPUT_DIR)/effects.bin: $(CURDIR)/../Effects/effects.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/effects.bin

all: $(OUTPUT_DIR)/music.bin
$(OUTPUT_DIR)/music.bin: $(CURDIR)/../Music/music.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/music.bin

all: $(OUTPUT_DIR)/systems.bin
$(OUTPUT_DIR)/systems.bin: $(CURDIR)/../Systems/systems.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/systems.bin

all: $(OUTPUT_DIR)/itemicons.bin
$(OUTPUT_DIR)/itemicons.bin: $(CURDIR)/../Items/icons.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/itemicons.bin

all: $(OUTPUT_DIR)/npcs.bin $(OUTPUT_DIR)/scripts.bin
$(OUTPUT_DIR)/npcs.bin: $(CURDIR)/../NPCs/npcs.bin
	cp "$<" "$@"
$(OUTPUT_DIR)/scripts.bin: $(CURDIR)/../../packet194/released-scripts.bin
	cp "$<" "$@"

$(GEN_XISO): $(OUTPUT_DIR)/npcs.bin $(OUTPUT_DIR)/scripts.bin

all: $(OUTPUT_DIR)/portraits.bin
$(OUTPUT_DIR)/portraits.bin: $(CURDIR)/../Recovered195/portraits.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/portraits.bin

all: $(OUTPUT_DIR)/npcfx.bin
$(OUTPUT_DIR)/npcfx.bin: $(CURDIR)/../Recovered195/npcfx.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/npcfx.bin

all: $(OUTPUT_DIR)/mercenary.bin
$(OUTPUT_DIR)/mercenary.bin: $(CURDIR)/../Presentation/mercenary.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/mercenary.bin

all: $(OUTPUT_DIR)/water.bin
$(OUTPUT_DIR)/water.bin: $(CURDIR)/../Water/water.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/water.bin

all: $(OUTPUT_DIR)/chapter1.bin
$(OUTPUT_DIR)/chapter1.bin: $(CURDIR)/../Recovered195/chapter1.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/chapter1.bin

all: $(OUTPUT_DIR)/minimaps.bin
$(OUTPUT_DIR)/minimaps.bin: $(CURDIR)/../Interface/minimaps.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/minimaps.bin

ifneq ($(wildcard $(CURDIR)/../Recovered195/campaign.bin),)
all: $(OUTPUT_DIR)/campaign.bin
$(OUTPUT_DIR)/campaign.bin: $(CURDIR)/../Recovered195/campaign.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/campaign.bin
endif

# One disc-loaded campaign portrait at a time; no complete expression bank in RAM.
all: $(OUTPUT_DIR)/storyportraits.bin
$(OUTPUT_DIR)/storyportraits.bin: $(CURDIR)/../Recovered195/storyportraits.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/storyportraits.bin

# Newly authored eight-direction cabinets, streamed one pose per visible machine.
all: $(OUTPUT_DIR)/guildviews.bin
$(OUTPUT_DIR)/guildviews.bin: $(CURDIR)/../Guild/Directional197/views.bin
	cp "$<" "$@"
$(GEN_XISO): $(OUTPUT_DIR)/guildviews.bin
