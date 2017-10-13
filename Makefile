CC=sdcc
CFLAGS=-DSTM8S103 --opt-code-size -mstm8 -I inc -I src -L lib --std-sdcc99

C_FILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix src/,$(notdir $(C_FILES:.c=.rel)))

OBJ_FILES_MANUAL := stm8s_it.rel src/stm8s_rst.rel src/stm8s_itc.rel src/stm8s_spi.rel src/stm8s_tim2.rel src/stm8s_flash.rel src/stm8s_awu.rel src/stm8s_i2c.rel src/stm8s_clk.rel src/stm8s_iwdg.rel src/stm8s_gpio.rel src/stm8s_exti.rel  src/stm8s_uart1.rel src/stm8s_wwdg.rel src/stm8s_tim1.rel src/stm8s_beep.rel src/stm8s_tim4.rel src/stm8s_itc.rel

all: lib/stm8s.lib  projects/LEDstripe.ihx

clean:
	-rm -f *.asm  *.lst  *.rel  *.sym
	-rm -f src/*.asm  src/*.lst  src/*.rel  src/*.sym

%.obj : %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.rel : %.c
	$(CC) -c $(CFLAGS) $< -o $@

lib/stm8s.lib : $(OBJ_FILES_MANUAL)
	sdcclib -r $@ $(OBJ_FILES_MANUAL)

projects/%.ihx : projects/%.c lib/stm8s.lib
	$(CC) $(CFLAGS) -lstm8s --out-fmt-ihx $<  -o $@
	sudo stm8flash -c stlinkv2 -w projects/LEDstripe.ihx -p stm8s103f3
