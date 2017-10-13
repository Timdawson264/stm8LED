                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.6.0 #9615 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module stm8s_gpio
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _assert_failed
                                     12 	.globl _GPIO_DeInit
                                     13 	.globl _GPIO_Init
                                     14 	.globl _GPIO_Write
                                     15 	.globl _GPIO_WriteHigh
                                     16 	.globl _GPIO_WriteLow
                                     17 	.globl _GPIO_WriteReverse
                                     18 	.globl _GPIO_ReadOutputData
                                     19 	.globl _GPIO_ReadInputData
                                     20 	.globl _GPIO_ReadInputPin
                                     21 	.globl _GPIO_ExternalPullUpConfig
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area DATA
                                     26 ;--------------------------------------------------------
                                     27 ; ram data
                                     28 ;--------------------------------------------------------
                                     29 	.area INITIALIZED
                                     30 ;--------------------------------------------------------
                                     31 ; absolute external ram data
                                     32 ;--------------------------------------------------------
                                     33 	.area DABS (ABS)
                                     34 ;--------------------------------------------------------
                                     35 ; global & static initialisations
                                     36 ;--------------------------------------------------------
                                     37 	.area HOME
                                     38 	.area GSINIT
                                     39 	.area GSFINAL
                                     40 	.area GSINIT
                                     41 ;--------------------------------------------------------
                                     42 ; Home
                                     43 ;--------------------------------------------------------
                                     44 	.area HOME
                                     45 	.area HOME
                                     46 ;--------------------------------------------------------
                                     47 ; code
                                     48 ;--------------------------------------------------------
                                     49 	.area CODE
                                     50 ;	src/stm8s_gpio.c: 53: void GPIO_DeInit(GPIO_TypeDef* GPIOx)
                                     51 ;	-----------------------------------------
                                     52 ;	 function GPIO_DeInit
                                     53 ;	-----------------------------------------
      0080C2                         54 _GPIO_DeInit:
      0080C2 89               [ 2]   55 	pushw	x
                                     56 ;	src/stm8s_gpio.c: 55: GPIOx->ODR = GPIO_ODR_RESET_VALUE; /* Reset Output Data Register */
      0080C3 16 05            [ 2]   57 	ldw	y, (0x05, sp)
      0080C5 17 01            [ 2]   58 	ldw	(0x01, sp), y
      0080C7 1E 01            [ 2]   59 	ldw	x, (0x01, sp)
      0080C9 7F               [ 1]   60 	clr	(x)
                                     61 ;	src/stm8s_gpio.c: 56: GPIOx->DDR = GPIO_DDR_RESET_VALUE; /* Reset Data Direction Register */
      0080CA 1E 01            [ 2]   62 	ldw	x, (0x01, sp)
      0080CC 5C               [ 2]   63 	incw	x
      0080CD 5C               [ 2]   64 	incw	x
      0080CE 7F               [ 1]   65 	clr	(x)
                                     66 ;	src/stm8s_gpio.c: 57: GPIOx->CR1 = GPIO_CR1_RESET_VALUE; /* Reset Control Register 1 */
      0080CF 1E 01            [ 2]   67 	ldw	x, (0x01, sp)
      0080D1 1C 00 03         [ 2]   68 	addw	x, #0x0003
      0080D4 7F               [ 1]   69 	clr	(x)
                                     70 ;	src/stm8s_gpio.c: 58: GPIOx->CR2 = GPIO_CR2_RESET_VALUE; /* Reset Control Register 2 */
      0080D5 1E 01            [ 2]   71 	ldw	x, (0x01, sp)
      0080D7 1C 00 04         [ 2]   72 	addw	x, #0x0004
      0080DA 7F               [ 1]   73 	clr	(x)
      0080DB 85               [ 2]   74 	popw	x
      0080DC 81               [ 4]   75 	ret
                                     76 ;	src/stm8s_gpio.c: 71: void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, GPIO_Mode_TypeDef GPIO_Mode)
                                     77 ;	-----------------------------------------
                                     78 ;	 function GPIO_Init
                                     79 ;	-----------------------------------------
      0080DD                         80 _GPIO_Init:
      0080DD 52 05            [ 2]   81 	sub	sp, #5
                                     82 ;	src/stm8s_gpio.c: 77: assert_param(IS_GPIO_MODE_OK(GPIO_Mode));
      0080DF 0D 0B            [ 1]   83 	tnz	(0x0b, sp)
      0080E1 27 53            [ 1]   84 	jreq	00116$
      0080E3 7B 0B            [ 1]   85 	ld	a, (0x0b, sp)
      0080E5 A1 40            [ 1]   86 	cp	a, #0x40
      0080E7 27 4D            [ 1]   87 	jreq	00116$
      0080E9 7B 0B            [ 1]   88 	ld	a, (0x0b, sp)
      0080EB A1 20            [ 1]   89 	cp	a, #0x20
      0080ED 27 47            [ 1]   90 	jreq	00116$
      0080EF 7B 0B            [ 1]   91 	ld	a, (0x0b, sp)
      0080F1 A1 60            [ 1]   92 	cp	a, #0x60
      0080F3 27 41            [ 1]   93 	jreq	00116$
      0080F5 7B 0B            [ 1]   94 	ld	a, (0x0b, sp)
      0080F7 A1 A0            [ 1]   95 	cp	a, #0xa0
      0080F9 27 3B            [ 1]   96 	jreq	00116$
      0080FB 7B 0B            [ 1]   97 	ld	a, (0x0b, sp)
      0080FD A1 E0            [ 1]   98 	cp	a, #0xe0
      0080FF 27 35            [ 1]   99 	jreq	00116$
      008101 7B 0B            [ 1]  100 	ld	a, (0x0b, sp)
      008103 A1 80            [ 1]  101 	cp	a, #0x80
      008105 27 2F            [ 1]  102 	jreq	00116$
      008107 7B 0B            [ 1]  103 	ld	a, (0x0b, sp)
      008109 A1 C0            [ 1]  104 	cp	a, #0xc0
      00810B 27 29            [ 1]  105 	jreq	00116$
      00810D 7B 0B            [ 1]  106 	ld	a, (0x0b, sp)
      00810F A1 B0            [ 1]  107 	cp	a, #0xb0
      008111 27 23            [ 1]  108 	jreq	00116$
      008113 7B 0B            [ 1]  109 	ld	a, (0x0b, sp)
      008115 A1 F0            [ 1]  110 	cp	a, #0xf0
      008117 27 1D            [ 1]  111 	jreq	00116$
      008119 7B 0B            [ 1]  112 	ld	a, (0x0b, sp)
      00811B A1 90            [ 1]  113 	cp	a, #0x90
      00811D 27 17            [ 1]  114 	jreq	00116$
      00811F 7B 0B            [ 1]  115 	ld	a, (0x0b, sp)
      008121 A1 D0            [ 1]  116 	cp	a, #0xd0
      008123 27 11            [ 1]  117 	jreq	00116$
      008125 AE 82 3E         [ 2]  118 	ldw	x, #___str_0+0
      008128 4B 4D            [ 1]  119 	push	#0x4d
      00812A 4B 00            [ 1]  120 	push	#0x00
      00812C 4B 00            [ 1]  121 	push	#0x00
      00812E 4B 00            [ 1]  122 	push	#0x00
      008130 89               [ 2]  123 	pushw	x
      008131 CD 00 00         [ 4]  124 	call	_assert_failed
      008134 5B 06            [ 2]  125 	addw	sp, #6
      008136                        126 00116$:
                                    127 ;	src/stm8s_gpio.c: 78: assert_param(IS_GPIO_PIN_OK(GPIO_Pin));
      008136 0D 0A            [ 1]  128 	tnz	(0x0a, sp)
      008138 26 11            [ 1]  129 	jrne	00151$
      00813A AE 82 3E         [ 2]  130 	ldw	x, #___str_0+0
      00813D 4B 4E            [ 1]  131 	push	#0x4e
      00813F 4B 00            [ 1]  132 	push	#0x00
      008141 4B 00            [ 1]  133 	push	#0x00
      008143 4B 00            [ 1]  134 	push	#0x00
      008145 89               [ 2]  135 	pushw	x
      008146 CD 00 00         [ 4]  136 	call	_assert_failed
      008149 5B 06            [ 2]  137 	addw	sp, #6
      00814B                        138 00151$:
                                    139 ;	src/stm8s_gpio.c: 81: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      00814B 16 08            [ 2]  140 	ldw	y, (0x08, sp)
      00814D 17 04            [ 2]  141 	ldw	(0x04, sp), y
      00814F 1E 04            [ 2]  142 	ldw	x, (0x04, sp)
      008151 1C 00 04         [ 2]  143 	addw	x, #0x0004
      008154 1F 01            [ 2]  144 	ldw	(0x01, sp), x
      008156 1E 01            [ 2]  145 	ldw	x, (0x01, sp)
      008158 F6               [ 1]  146 	ld	a, (x)
      008159 88               [ 1]  147 	push	a
      00815A 7B 0B            [ 1]  148 	ld	a, (0x0b, sp)
      00815C 43               [ 1]  149 	cpl	a
      00815D 6B 04            [ 1]  150 	ld	(0x04, sp), a
      00815F 84               [ 1]  151 	pop	a
      008160 14 03            [ 1]  152 	and	a, (0x03, sp)
      008162 1E 01            [ 2]  153 	ldw	x, (0x01, sp)
      008164 F7               [ 1]  154 	ld	(x), a
                                    155 ;	src/stm8s_gpio.c: 98: GPIOx->DDR |= (uint8_t)GPIO_Pin;
      008165 1E 04            [ 2]  156 	ldw	x, (0x04, sp)
      008167 5C               [ 2]  157 	incw	x
      008168 5C               [ 2]  158 	incw	x
                                    159 ;	src/stm8s_gpio.c: 87: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x80) != (uint8_t)0x00) /* Output mode */
      008169 0D 0B            [ 1]  160 	tnz	(0x0b, sp)
      00816B 2A 20            [ 1]  161 	jrpl	00105$
                                    162 ;	src/stm8s_gpio.c: 91: GPIOx->ODR |= (uint8_t)GPIO_Pin;
      00816D 16 04            [ 2]  163 	ldw	y, (0x04, sp)
      00816F 90 F6            [ 1]  164 	ld	a, (y)
                                    165 ;	src/stm8s_gpio.c: 89: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x10) != (uint8_t)0x00) /* High level */
      008171 88               [ 1]  166 	push	a
      008172 7B 0C            [ 1]  167 	ld	a, (0x0c, sp)
      008174 A5 10            [ 1]  168 	bcp	a, #0x10
      008176 84               [ 1]  169 	pop	a
      008177 27 08            [ 1]  170 	jreq	00102$
                                    171 ;	src/stm8s_gpio.c: 91: GPIOx->ODR |= (uint8_t)GPIO_Pin;
      008179 1A 0A            [ 1]  172 	or	a, (0x0a, sp)
      00817B 16 04            [ 2]  173 	ldw	y, (0x04, sp)
      00817D 90 F7            [ 1]  174 	ld	(y), a
      00817F 20 06            [ 2]  175 	jra	00103$
      008181                        176 00102$:
                                    177 ;	src/stm8s_gpio.c: 95: GPIOx->ODR &= (uint8_t)(~(GPIO_Pin));
      008181 14 03            [ 1]  178 	and	a, (0x03, sp)
      008183 16 04            [ 2]  179 	ldw	y, (0x04, sp)
      008185 90 F7            [ 1]  180 	ld	(y), a
      008187                        181 00103$:
                                    182 ;	src/stm8s_gpio.c: 98: GPIOx->DDR |= (uint8_t)GPIO_Pin;
      008187 F6               [ 1]  183 	ld	a, (x)
      008188 1A 0A            [ 1]  184 	or	a, (0x0a, sp)
      00818A F7               [ 1]  185 	ld	(x), a
      00818B 20 04            [ 2]  186 	jra	00106$
      00818D                        187 00105$:
                                    188 ;	src/stm8s_gpio.c: 103: GPIOx->DDR &= (uint8_t)(~(GPIO_Pin));
      00818D F6               [ 1]  189 	ld	a, (x)
      00818E 14 03            [ 1]  190 	and	a, (0x03, sp)
      008190 F7               [ 1]  191 	ld	(x), a
      008191                        192 00106$:
                                    193 ;	src/stm8s_gpio.c: 112: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      008191 1E 04            [ 2]  194 	ldw	x, (0x04, sp)
      008193 1C 00 03         [ 2]  195 	addw	x, #0x0003
                                    196 ;	src/stm8s_gpio.c: 110: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x40) != (uint8_t)0x00) /* Pull-Up or Push-Pull */
      008196 7B 0B            [ 1]  197 	ld	a, (0x0b, sp)
      008198 A5 40            [ 1]  198 	bcp	a, #0x40
      00819A 27 06            [ 1]  199 	jreq	00108$
                                    200 ;	src/stm8s_gpio.c: 112: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      00819C F6               [ 1]  201 	ld	a, (x)
      00819D 1A 0A            [ 1]  202 	or	a, (0x0a, sp)
      00819F F7               [ 1]  203 	ld	(x), a
      0081A0 20 04            [ 2]  204 	jra	00109$
      0081A2                        205 00108$:
                                    206 ;	src/stm8s_gpio.c: 116: GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
      0081A2 F6               [ 1]  207 	ld	a, (x)
      0081A3 14 03            [ 1]  208 	and	a, (0x03, sp)
      0081A5 F7               [ 1]  209 	ld	(x), a
      0081A6                        210 00109$:
                                    211 ;	src/stm8s_gpio.c: 123: if ((((uint8_t)(GPIO_Mode)) & (uint8_t)0x20) != (uint8_t)0x00) /* Interrupt or Slow slope */
      0081A6 7B 0B            [ 1]  212 	ld	a, (0x0b, sp)
      0081A8 A5 20            [ 1]  213 	bcp	a, #0x20
      0081AA 27 0A            [ 1]  214 	jreq	00111$
                                    215 ;	src/stm8s_gpio.c: 125: GPIOx->CR2 |= (uint8_t)GPIO_Pin;
      0081AC 1E 01            [ 2]  216 	ldw	x, (0x01, sp)
      0081AE F6               [ 1]  217 	ld	a, (x)
      0081AF 1A 0A            [ 1]  218 	or	a, (0x0a, sp)
      0081B1 1E 01            [ 2]  219 	ldw	x, (0x01, sp)
      0081B3 F7               [ 1]  220 	ld	(x), a
      0081B4 20 08            [ 2]  221 	jra	00113$
      0081B6                        222 00111$:
                                    223 ;	src/stm8s_gpio.c: 129: GPIOx->CR2 &= (uint8_t)(~(GPIO_Pin));
      0081B6 1E 01            [ 2]  224 	ldw	x, (0x01, sp)
      0081B8 F6               [ 1]  225 	ld	a, (x)
      0081B9 14 03            [ 1]  226 	and	a, (0x03, sp)
      0081BB 1E 01            [ 2]  227 	ldw	x, (0x01, sp)
      0081BD F7               [ 1]  228 	ld	(x), a
      0081BE                        229 00113$:
      0081BE 5B 05            [ 2]  230 	addw	sp, #5
      0081C0 81               [ 4]  231 	ret
                                    232 ;	src/stm8s_gpio.c: 141: void GPIO_Write(GPIO_TypeDef* GPIOx, uint8_t PortVal)
                                    233 ;	-----------------------------------------
                                    234 ;	 function GPIO_Write
                                    235 ;	-----------------------------------------
      0081C1                        236 _GPIO_Write:
                                    237 ;	src/stm8s_gpio.c: 143: GPIOx->ODR = PortVal;
      0081C1 1E 03            [ 2]  238 	ldw	x, (0x03, sp)
      0081C3 7B 05            [ 1]  239 	ld	a, (0x05, sp)
      0081C5 F7               [ 1]  240 	ld	(x), a
      0081C6 81               [ 4]  241 	ret
                                    242 ;	src/stm8s_gpio.c: 154: void GPIO_WriteHigh(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    243 ;	-----------------------------------------
                                    244 ;	 function GPIO_WriteHigh
                                    245 ;	-----------------------------------------
      0081C7                        246 _GPIO_WriteHigh:
                                    247 ;	src/stm8s_gpio.c: 156: GPIOx->ODR |= (uint8_t)PortPins;
      0081C7 1E 03            [ 2]  248 	ldw	x, (0x03, sp)
      0081C9 F6               [ 1]  249 	ld	a, (x)
      0081CA 1A 05            [ 1]  250 	or	a, (0x05, sp)
      0081CC F7               [ 1]  251 	ld	(x), a
      0081CD 81               [ 4]  252 	ret
                                    253 ;	src/stm8s_gpio.c: 167: void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    254 ;	-----------------------------------------
                                    255 ;	 function GPIO_WriteLow
                                    256 ;	-----------------------------------------
      0081CE                        257 _GPIO_WriteLow:
      0081CE 88               [ 1]  258 	push	a
                                    259 ;	src/stm8s_gpio.c: 169: GPIOx->ODR &= (uint8_t)(~PortPins);
      0081CF 1E 04            [ 2]  260 	ldw	x, (0x04, sp)
      0081D1 F6               [ 1]  261 	ld	a, (x)
      0081D2 6B 01            [ 1]  262 	ld	(0x01, sp), a
      0081D4 7B 06            [ 1]  263 	ld	a, (0x06, sp)
      0081D6 43               [ 1]  264 	cpl	a
      0081D7 14 01            [ 1]  265 	and	a, (0x01, sp)
      0081D9 F7               [ 1]  266 	ld	(x), a
      0081DA 84               [ 1]  267 	pop	a
      0081DB 81               [ 4]  268 	ret
                                    269 ;	src/stm8s_gpio.c: 180: void GPIO_WriteReverse(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
                                    270 ;	-----------------------------------------
                                    271 ;	 function GPIO_WriteReverse
                                    272 ;	-----------------------------------------
      0081DC                        273 _GPIO_WriteReverse:
                                    274 ;	src/stm8s_gpio.c: 182: GPIOx->ODR ^= (uint8_t)PortPins;
      0081DC 1E 03            [ 2]  275 	ldw	x, (0x03, sp)
      0081DE F6               [ 1]  276 	ld	a, (x)
      0081DF 18 05            [ 1]  277 	xor	a, (0x05, sp)
      0081E1 F7               [ 1]  278 	ld	(x), a
      0081E2 81               [ 4]  279 	ret
                                    280 ;	src/stm8s_gpio.c: 191: uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
                                    281 ;	-----------------------------------------
                                    282 ;	 function GPIO_ReadOutputData
                                    283 ;	-----------------------------------------
      0081E3                        284 _GPIO_ReadOutputData:
                                    285 ;	src/stm8s_gpio.c: 193: return ((uint8_t)GPIOx->ODR);
      0081E3 1E 03            [ 2]  286 	ldw	x, (0x03, sp)
      0081E5 F6               [ 1]  287 	ld	a, (x)
      0081E6 81               [ 4]  288 	ret
                                    289 ;	src/stm8s_gpio.c: 202: uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
                                    290 ;	-----------------------------------------
                                    291 ;	 function GPIO_ReadInputData
                                    292 ;	-----------------------------------------
      0081E7                        293 _GPIO_ReadInputData:
                                    294 ;	src/stm8s_gpio.c: 204: return ((uint8_t)GPIOx->IDR);
      0081E7 1E 03            [ 2]  295 	ldw	x, (0x03, sp)
      0081E9 E6 01            [ 1]  296 	ld	a, (0x1, x)
      0081EB 81               [ 4]  297 	ret
                                    298 ;	src/stm8s_gpio.c: 213: BitStatus GPIO_ReadInputPin(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
                                    299 ;	-----------------------------------------
                                    300 ;	 function GPIO_ReadInputPin
                                    301 ;	-----------------------------------------
      0081EC                        302 _GPIO_ReadInputPin:
                                    303 ;	src/stm8s_gpio.c: 215: return ((BitStatus)(GPIOx->IDR & (uint8_t)GPIO_Pin));
      0081EC 1E 03            [ 2]  304 	ldw	x, (0x03, sp)
      0081EE E6 01            [ 1]  305 	ld	a, (0x1, x)
      0081F0 14 05            [ 1]  306 	and	a, (0x05, sp)
      0081F2 81               [ 4]  307 	ret
                                    308 ;	src/stm8s_gpio.c: 225: void GPIO_ExternalPullUpConfig(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin, FunctionalState NewState)
                                    309 ;	-----------------------------------------
                                    310 ;	 function GPIO_ExternalPullUpConfig
                                    311 ;	-----------------------------------------
      0081F3                        312 _GPIO_ExternalPullUpConfig:
      0081F3 88               [ 1]  313 	push	a
                                    314 ;	src/stm8s_gpio.c: 228: assert_param(IS_GPIO_PIN_OK(GPIO_Pin));
      0081F4 0D 06            [ 1]  315 	tnz	(0x06, sp)
      0081F6 26 11            [ 1]  316 	jrne	00107$
      0081F8 AE 82 3E         [ 2]  317 	ldw	x, #___str_0+0
      0081FB 4B E4            [ 1]  318 	push	#0xe4
      0081FD 4B 00            [ 1]  319 	push	#0x00
      0081FF 4B 00            [ 1]  320 	push	#0x00
      008201 4B 00            [ 1]  321 	push	#0x00
      008203 89               [ 2]  322 	pushw	x
      008204 CD 00 00         [ 4]  323 	call	_assert_failed
      008207 5B 06            [ 2]  324 	addw	sp, #6
      008209                        325 00107$:
                                    326 ;	src/stm8s_gpio.c: 229: assert_param(IS_FUNCTIONALSTATE_OK(NewState));
      008209 0D 07            [ 1]  327 	tnz	(0x07, sp)
      00820B 27 17            [ 1]  328 	jreq	00109$
      00820D 7B 07            [ 1]  329 	ld	a, (0x07, sp)
      00820F A1 01            [ 1]  330 	cp	a, #0x01
      008211 27 11            [ 1]  331 	jreq	00109$
      008213 AE 82 3E         [ 2]  332 	ldw	x, #___str_0+0
      008216 4B E5            [ 1]  333 	push	#0xe5
      008218 4B 00            [ 1]  334 	push	#0x00
      00821A 4B 00            [ 1]  335 	push	#0x00
      00821C 4B 00            [ 1]  336 	push	#0x00
      00821E 89               [ 2]  337 	pushw	x
      00821F CD 00 00         [ 4]  338 	call	_assert_failed
      008222 5B 06            [ 2]  339 	addw	sp, #6
      008224                        340 00109$:
                                    341 ;	src/stm8s_gpio.c: 233: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      008224 1E 04            [ 2]  342 	ldw	x, (0x04, sp)
      008226 1C 00 03         [ 2]  343 	addw	x, #0x0003
                                    344 ;	src/stm8s_gpio.c: 231: if (NewState != DISABLE) /* External Pull-Up Set*/
      008229 0D 07            [ 1]  345 	tnz	(0x07, sp)
      00822B 27 06            [ 1]  346 	jreq	00102$
                                    347 ;	src/stm8s_gpio.c: 233: GPIOx->CR1 |= (uint8_t)GPIO_Pin;
      00822D F6               [ 1]  348 	ld	a, (x)
      00822E 1A 06            [ 1]  349 	or	a, (0x06, sp)
      008230 F7               [ 1]  350 	ld	(x), a
      008231 20 09            [ 2]  351 	jra	00104$
      008233                        352 00102$:
                                    353 ;	src/stm8s_gpio.c: 236: GPIOx->CR1 &= (uint8_t)(~(GPIO_Pin));
      008233 F6               [ 1]  354 	ld	a, (x)
      008234 6B 01            [ 1]  355 	ld	(0x01, sp), a
      008236 7B 06            [ 1]  356 	ld	a, (0x06, sp)
      008238 43               [ 1]  357 	cpl	a
      008239 14 01            [ 1]  358 	and	a, (0x01, sp)
      00823B F7               [ 1]  359 	ld	(x), a
      00823C                        360 00104$:
      00823C 84               [ 1]  361 	pop	a
      00823D 81               [ 4]  362 	ret
                                    363 	.area CODE
      00823E                        364 ___str_0:
      00823E 73 72 63 2F 73 74 6D   365 	.ascii "src/stm8s_gpio.c"
             38 73 5F 67 70 69 6F
             2E 63
      00824E 00                     366 	.db 0x00
                                    367 	.area INITIALIZER
                                    368 	.area CABS (ABS)
