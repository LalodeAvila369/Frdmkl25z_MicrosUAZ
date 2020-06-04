//avared98@eddeav98: GitHub_<gitBranch.ignore>
//avared98@eddeav98: master_branch <Eduaro de Avila Armenta>
//avared98@eddeav98: title_gitbranch <Semáforos 2° Proyecto Microcontroladores>
//

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_tpm.h"

//Componentes Cruce Norte a Sur GPIOB
#define NGreen 0u
#define NYellow 1u
#define NRed 2u
#define NBlue 3u
#define NSense 2u

//Componentes Cruce Sur a Norte GPIOE
#define SGreen 20u
#define SYellow 21u
#define SRed 22u
#define SBlue 23u
#define SSense 29u

//Componentes Cruce Este a Oeste GPIOC
#define EGreen 5u
#define EYellow 4u
#define ERed 3u
#define EBlue 0u
#define ESense 7u

//Componentes Cruce Oeste a Este	(GPIOC-GPIOA)
#define WGreen 4u
#define WYellow 12u
#define WRed 4u
#define WBlue 2u
#define WSense 1u
#define PeopleSense 13u

typedef struct{
	uint16_t TIMER_MOD;
	//Componentes N-S
	uint8_t NVerde;
	uint8_t NRojo;
	uint8_t NAmarillo;
	uint8_t NAzul;
	//Componentes S-N
	uint8_t SVerde;
	uint8_t SRojo;
	uint8_t SAmarillo;
	uint8_t SAzul;
	//Componentes E-O
	uint8_t EVerde;
	uint8_t ERojo;
	uint8_t EAmarillo;
	uint8_t EAzul;
	//Componentes O-E
	uint8_t OVerde;
	uint8_t ORojo;
	uint8_t OAmarillo;
	uint8_t OAzul;
}state;

int main(void) {

  	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	BOARD_InitDebugConsole();

  	//Configuracion TPM
    tpm_config_t config;
    TPM_GetDefaultConfig(&config);
	config.prescale= kTPM_Prescale_Divide_128;
	TPM_Init(TPM0, &config);
	TPM_Init(TPM1, &config);
	TPM_Init(TPM2, &config);

	state FSM[34];
	FSM[0]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=1u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 1u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 1u, .ERojo = 0u, .EAzul=0u, /*OE*/.OVerde = 0u, .OAmarillo = 1u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=2560u};		//Estado de Parpadeo Amarillo (IDLE)
	FSM[1]=(state ){/*NS*/.NVerde= 1u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 1u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*OE*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=2024u};		//Estado Verde (NS-SN)/ Rojo (EO-OE) Sensado, t=7s
	FSM[2]=(state ){/*NS*/.NVerde= 1u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 1u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*OE*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=2024u}; 		//Estado Verde Sin Vuelta (NS-SN) / Rojo (EO-OE), t=7s
	FSM[3]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*OE*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u}; 						//Estado Parpadeo Verde (NS-SN) / Rojo (EO-OE), t=1s
	FSM[4]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=1u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 1u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*OE*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=512u}; 		//Estado Amarillo (NS-SN) / Rojo (EO-OE), t=2s

	/*C  A  M  B  I  O     S  E  M  A  F  O  R  O  S        D  E       S  E  N  T  I  D  O */
	FSM[5]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 1u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 1u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=2024u};		// Estado Rojo (NS-SN)/ Verde (EO-OE) Sensado, t=7s
	FSM[6]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 1u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 1u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=2024u};		//Estado Rojo (NS-SN) / Verde Sin Vuelta (EO-OE), t=7s
	FSM[7]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u};						//Estado Rojo (NS-SN) / Parpadeo Verde (EO-OE), t=1s
	FSM[8]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 1u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 1u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=512u};		//Estado ROJO (NS-SN) / Amarillo (EO-OE), t=2s

	/* A  Q  U  I     E  M  P  I  E  Z  A  N       E  S  T  A  D  O  S      C  O  N        V  U  E  L  T  A*/

	/*P A R A        N S e n s o r  ==  1  & &   S S e n s o r ==  0 */
	FSM[9]=(state ){/*NS*/.NVerde= 1u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u};						//Estado Verde NS / Verde Parpadeo SN / Rojo (EO-OE), t=1s
	FSM[10]=(state ){/*NS*/.NVerde=1u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 1u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Verde NS / Amarillo SN / Rojo (EO-OE), t=2s
	FSM[11]=(state ){/*NS*/.NVerde=1u, .NAmarillo=0u, .NRojo=0u, .NAzul=1u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=1024u};		//Estado Verde y Vuelta NS / Rojo SN / Rojo (EO-OE), t=4s
	FSM[12]=(state ){/*NS*/.NVerde=0u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u};						//Estado Verde y Vuelta Parpadeo NS / Rojo SN / Rojo (EO-OE), t=1s
	FSM[13]=(state ){/*NS*/.NVerde=0u, .NAmarillo=1u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Amarillo NS / Rojo SN / Rojo (EO-OE), t=2s

	/*P A R A        N S e n s o r  ==  0  & &   S S e n s o r ==  1 */
	FSM[14]=(state ){/*NS*/.NVerde=0u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 1u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u};						//Estado Verde Parpadeo NS / Verde SN / Rojo (EO-OE), t=1s
	FSM[15]=(state ){/*NS*/.NVerde=0u, .NAmarillo=1u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 1u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Amarillo NS / Verde SN / Rojo (EO-OE), t=2s
	FSM[16]=(state ){/*NS*/.NVerde=0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 1u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=1u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=1024u};		//Estado Rojo NS / Verde y Vuelta SN / Rojo (EO-OE), t=4s
	FSM[17]=(state ){/*NS*/.NVerde=0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u};						//Estado Rojo NS / Verde y Vuelta Parpadeo SN / Rojo (EO-OE), t=1s
	FSM[18]=(state ){/*NS*/.NVerde=0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 1u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Rojo NS / Amarillo SN / Rojo (EO-OE), t=2s

	/*S  E  N  S  O  R  E  S        D  E        E  S  T  E     Y     O  E  S  T  E*/

	/*P A R A        E S e n s o r  ==  1  & &   W S e n s o r ==  0 */
	FSM[19]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 1u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u};						//Estado Rojo (NS-SN)/ Verde EO / Verde Parpadeo OE, t=1s
	FSM[20]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 1u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 1u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Verde EO / Amarillo OE / Rojo (NS-SN), t=2s
	FSM[21]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 1u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=1u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=1024u};		//Estado Verde y Vuelta EO / Rojo OE / Rojo (NS-SN), t=4s
	FSM[22]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u};						//Estado Verde y Vuelta Parpadeo EO / Rojo OE / Rojo (NS-SN), t=1s
	FSM[23]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 1u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Amarillo EO / Rojo OE / Rojo (NS-SN), t=2s

	/*P A R A        E S e n s o r  ==  0  & &   W S e n s o r ==  1 */
	FSM[24]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 1u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u};						//Estado Verde Parpadeo EO / Verde OE / Rojo (NS-SN), t=1s
	FSM[25]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 1u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 1u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=512u}; 		//Estado Amarillo EO / Verde OE / Rojo (NS-SN), t=2s
	FSM[26]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 1u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=1u, .TIMER_MOD=1024u}; 	//Estado Rojo EO / Verde y Vuelta OE / Rojo (NS-SN), t=4s
	FSM[27]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u};						//Estado Rojo EO / Verde y Vuelta Parpadeo OE / Rojo (NS-SN), t=1s
	FSM[28]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 1u, .ORojo = 0u, .OAzul=0u, .TIMER_MOD=512u};		//Estado Rojo EO / Amarillo OE / Rojo (NS-SN), t=2s


	/*P A R A        N S e n s o r  ==  1  & &   S S e n s o r ==  1 */
	FSM[29]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=0u, .NAzul=1u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=1u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u, .TIMER_MOD=1024u};		//Estado Azul (NS-SN), Rojo (EO-OE), t=4s
	FSM[30]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 1u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 1u, .OAzul=0u};						//Estado Parpadeo Azul (NS-SN), Rojo (EO-OE), t=1s

	/*P A R A        E S e n s o r  ==  1  & &   W S e n s o r ==  1 */
	FSM[31]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=1u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=1u, .TIMER_MOD=1024u};		//Estado Azul (EO-OE), Rojo (NS-SN), t=4s
	FSM[32]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=1u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 1u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u};						//Estado Parpadeo Azul (EO-OE), Rojo (NS-SN), t=1s
	FSM[33]=(state ){/*NS*/.NVerde= 0u, .NAmarillo=0u, .NRojo=0u, .NAzul=0u, /*SN*/ .SVerde = 0u, .SAmarillo = 0u, .SRojo = 0u, .SAzul=0u,/*EO*/ .EVerde = 0u, .EAmarillo = 0u, .ERojo = 0u, .EAzul=0u, /*EO*/.OVerde = 0u, .OAmarillo = 0u, .ORojo = 0u, .OAzul=0u};						//Estado Parpadeo Azul (EO-OE), Rojo (NS-SN), t=1s




	uint8_t estado_reg=0;
	uint8_t estado=0;
	uint8_t Timer_init=0;
	uint32_t TIMER_FLAG;
	uint32_t Mask= 1u<<8u;
	uint32_t Mask2= 1u<<8u;
	uint32_t Mask_Off2 = Mask2;
	uint32_t Mask_Off = Mask;
	uint8_t NSensor;
	uint8_t SSensor;
	uint8_t ESensor;
	uint8_t WSensor;
	uint8_t NSensor_reg=1;
	uint8_t SSensor_reg=1;
	uint8_t ESensor_reg=1;
	uint8_t WSensor_reg=1;
	uint8_t People;
	uint8_t actual_state=0;

	//actual_state=estado;

	int Counter = 0;


    while(1) {
    	GPIO_WritePinOutput(GPIOB, NGreen, FSM[estado].NVerde);
    	GPIO_WritePinOutput(GPIOB, NYellow, FSM[estado].NAmarillo);
    	GPIO_WritePinOutput(GPIOB, NRed, FSM[estado].NRojo);
    	GPIO_WritePinOutput(GPIOB, NBlue, FSM[estado].NAzul);
    	GPIO_WritePinOutput(GPIOE, SGreen, FSM[estado].SVerde);
    	GPIO_WritePinOutput(GPIOE, SYellow, FSM[estado].SAmarillo);
    	GPIO_WritePinOutput(GPIOE, SRed, FSM[estado].SRojo);
    	GPIO_WritePinOutput(GPIOE, SBlue, FSM[estado].SAzul);
    	GPIO_WritePinOutput(GPIOC, EGreen, FSM[estado].EVerde);
		GPIO_WritePinOutput(GPIOC, EYellow, FSM[estado].EAmarillo);
		GPIO_WritePinOutput(GPIOC, ERed, FSM[estado].ERojo);
		GPIO_WritePinOutput(GPIOC, EBlue, FSM[estado].EAzul);
		GPIO_WritePinOutput(GPIOA, WGreen, FSM[estado].OVerde);
		GPIO_WritePinOutput(GPIOA, WYellow, FSM[estado].OAmarillo);
		GPIO_WritePinOutput(GPIOD, WRed, FSM[estado].ORojo);
		GPIO_WritePinOutput(GPIOA, WBlue, FSM[estado].OAzul);

    	NSensor=GPIO_ReadPinInput(GPIOC, NSense);
    	SSensor=GPIO_ReadPinInput(GPIOE, SSense);
    	ESensor=GPIO_ReadPinInput(GPIOC, ESense);
    	WSensor=GPIO_ReadPinInput(GPIOA, WSense);
    	People= GPIO_ReadPinInput(GPIOA, PeopleSense);

    	if(NSensor == 0){
			NSensor_reg=0;
    	}

    	if(SSensor == 0){
    		SSensor_reg=0;
    	}

    	if(ESensor == 0){
    		ESensor_reg=0;
    	}

    	if(WSensor == 0){
    		WSensor_reg=0;
    	}






    	TIMER_FLAG=TPM_GetStatusFlags(TPM0);

    	if(People==0){
    		estado=33;
    	}


    	switch(estado){
    	case 0:														//Estado de Parpadeo Amarillo (IDLE)
    		do{
				TPM_SetTimerPeriod(TPM1, 256u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOB, 1u<<1u);
				GPIO_TogglePinsOutput(GPIOE, 1u<<21u);
				GPIO_TogglePinsOutput(GPIOC, 1u<<4u);
				GPIO_TogglePinsOutput(GPIOA, 1u<<12u);
				while(!(TPM1->STATUS & Mask)){ 		//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &=Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}

			}while(Counter<=9);
    		Counter=0;
    		actual_state=estado;
    		estado=1;
    	break;

    	case 1:														 // Estado Verde (NS-SN)/ Rojo (EO-OE) Sensado, t=7s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[1].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<8u);
				Timer_init=0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;

				if(NSensor_reg == 1 && SSensor_reg==1){
					estado_reg=0;
					NSensor_reg = 1;
					SSensor_reg = 1;
					estado = 2;
				}else if(NSensor_reg == 0 && SSensor_reg==1){
					NSensor_reg = 1;
					SSensor_reg = 1;
					estado = 9;
				}else if(NSensor_reg == 1 && SSensor_reg==0){
					NSensor_reg = 1;
					SSensor_reg = 1;
					estado = 14;
				}else if(NSensor_reg == 0 && SSensor_reg==0){
					estado_reg=1;
					NSensor_reg = 1;
					SSensor_reg = 1;
					estado = 3;
				}
			}
		break;

    	case 2:														//Estado Verde Sin Vuelta (NS-SN) / Rojo (EO-OE), t=7s                                      En estados 1-3, cumplimiento de 15 s Verde
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[2].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}


			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<8u);
				Timer_init=0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado=3;
			}
		break;

    	case 3:													//Estado Parpadeo Verde (NS-SN) / Rojo (EO-OE), t=1s
    		actual_state=estado;
			do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOB, 1u<<0u);
				GPIO_TogglePinsOutput(GPIOE, 1u<<20u);
				while(!(TPM1->STATUS & Mask)){ 		//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &=Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}

			}while(Counter<=9);
			Counter=0;
			estado=4;
    	break;

    	case 4:													//Estado Amarillo (NS-SN) / Rojo (EO-OE), t=2s												Cumplimiento de 2s de Amarillo
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[4].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}


			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<8u);
				Timer_init=0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				if(estado_reg==0){
					estado=5;
				}else if(estado_reg==1){
					estado=29;
				}

			}
    	break;

    	/*C  A  M  B  I  O     S  E  M  A  F  O  R  O  S        D  E       S  E  N  T  I  D  O */


    	case 5:														 // Estado Rojo (NS-SN)/ Verde (EO-OE) Sensado, t=7s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[5].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<8u);
				Timer_init=0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;

				if(ESensor_reg == 1 && WSensor_reg==1){
					estado_reg=0;
					ESensor_reg = 1;
					WSensor_reg = 1;
					estado = 6;
				}else if(ESensor_reg == 0 && WSensor_reg==1){
					ESensor_reg = 1;
					WSensor_reg = 1;
					estado = 19;
				}else if(ESensor_reg == 1 && WSensor_reg==0){
					ESensor_reg = 1;
					WSensor_reg = 1;
					estado = 24;
				}else if(WSensor_reg == 0 && ESensor_reg==0){
					ESensor_reg = 1;
					WSensor_reg = 1;
					estado_reg=1;
					estado = 7;
				}
			}
		break;

    	case 6:														//Estado Rojo (NS-SN) / Verde Sin Vuelta (EO-OE), t=7s                                      En estados 1-3, cumplimiento de 15 s Verde
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[6].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}


			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<8u);
				Timer_init=0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado=7;
			}
		break;

    	case 7:													//Estado Rojo (NS-SN) / Parpadeo Verde (EO-OE), t=1s
    		actual_state=estado;
			do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOC, 1u<<5u);
				GPIO_TogglePinsOutput(GPIOA, 1u<<4u);
				while(!(TPM1->STATUS & Mask)){ 		//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &=Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}

			}while(Counter<=9);
			Counter=0;
			estado=8;
    	break;

    	case 8:													//Estado ROJO (NS-SN) / Amarillo (EO-OE), t=2s												Cumplimiento de 2s de Amarillo
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[8].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}


			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<8u);
				Timer_init=0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				if(estado_reg==0){
					estado=1;
				}else if(estado_reg==1){
					estado=31;
				}
			}
    	break;


    	/* A  Q  U  I     E  M  P  I  E  Z  A  N       E  S  T  A  D  O  S      C  O  N        V  U  E  L  T  A*/


    	/*P A R A        N S e n s o r  ==  1  & &   S S e n s o r ==  0 */

    	case 9:												//Estado Verde NS / Verde Parpadeo SN / Rojo (EO-OE), t=1s
    		actual_state=estado;
    		do{
    			TPM_SetTimerPeriod(TPM1, 64u);
    			TPM_StartTimer(TPM1, kTPM_SystemClock);
    			GPIO_TogglePinsOutput(GPIOE, 1u<<20u);
    			while(!(TPM1->STATUS & Mask)){			//Wait
    			}

    			if(TPM1->STATUS & Mask){
    				TPM1->STATUS &= Mask_Off;
    				Counter=Counter+1;
    				TPM_StopTimer(TPM1);
    				TPM1->CNT=0;
    			}
    		}while(Counter<=9);
    		Counter=0;
    		estado=10;
    	break;

    	case 10:											//Estado Verde NS / Amarillo SN / Rojo (EO-OE), t=2s								S e  c u m p l e n  l o s  10 s
    		actual_state=estado;
    		if(Timer_init==0){
    			Timer_init=1;
    			TPM_SetTimerPeriod(TPM0, FSM[10].TIMER_MOD);
    			TPM_StartTimer(TPM0, kTPM_SystemClock);
    		}

    		if(TIMER_FLAG){
    			TPM_ClearStatusFlags(TPM0, 1u<<8u);
    			Timer_init= 0;
    			TPM_StopTimer(TPM0);
    			TPM0->CNT=0;
    			estado= 11;
    		}
    	break;

    	case 11:											//Estado Verde y Vuelta NS / Rojo SN / Rojo (EO-OE), t=4s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[11].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 12;
			}
    	break;

    	case 12:											//Estado Verde y Vuelta Parpadeo NS / Rojo SN / Rojo (EO-OE), t=1s
    		actual_state=estado;
    		do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOB, 1u<<0u);
				GPIO_TogglePinsOutput(GPIOB, 1u<<3u);
				while(!(TPM1->STATUS & Mask)){			//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &= Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}
			}while(Counter<=9);
			Counter=0;
			estado=13;
		break;

    	case 13:											//Estado Amarillo NS / Rojo SN / Rojo (EO-OE), t=2s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[13].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 5;
			}
    	break;


    	/*P A R A        N S e n s o r  ==  0  & &   S S e n s o r ==  1 */

    	case 14:												//Estado Verde Parpadeo NS / Verde SN / Rojo (EO-OE), t=1s
    		actual_state=estado;
    		do{
    			TPM_SetTimerPeriod(TPM1, 64u);
    			TPM_StartTimer(TPM1, kTPM_SystemClock);
    			GPIO_TogglePinsOutput(GPIOB, 1u<<0u);
    			while(!(TPM1->STATUS & Mask)){			//Wait
    			}

    			if(TPM1->STATUS & Mask){
    				TPM1->STATUS &= Mask_Off;
    				Counter=Counter+1;
    				TPM_StopTimer(TPM1);
    				TPM1->CNT=0;
    			}
    		}while(Counter<=9);
    		Counter=0;
    		estado=15;
    	break;

    	case 15:											//Estado Amarillo NS / Verde SN / Rojo (EO-OE), t=2s								S e  c u m p l e n  l o s  10 s
    		actual_state=estado;
    		if(Timer_init==0){
    			Timer_init=1;
    			TPM_SetTimerPeriod(TPM0, FSM[15].TIMER_MOD);
    			TPM_StartTimer(TPM0, kTPM_SystemClock);
    		}

    		if(TIMER_FLAG){
    			TPM_ClearStatusFlags(TPM0, 1u<<8u);
    			Timer_init= 0;
    			TPM_StopTimer(TPM0);
    			TPM0->CNT=0;
    			estado= 16;
    		}
    	break;

    	case 16:											//Estado Rojo NS / Verde y Vuelta SN / Rojo (EO-OE), t=4s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[11].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 17;
			}
    	break;

    	case 17:											//Estado Rojo NS / Verde y Vuelta Parpadeo SN / Rojo (EO-OE), t=1s
    		actual_state=estado;
    		do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOE, 1u<<20u);
				GPIO_TogglePinsOutput(GPIOE, 1u<<23u);
				while(!(TPM1->STATUS & Mask)){			//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &= Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}
			}while(Counter<=9);
			Counter=0;
			estado=18;
		break;

    	case 18:											//Estado Rojo NS / Amarillo SN / Rojo (EO-OE), t=2s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[18].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 5;
			}
    	break;


    	/*S  E  N  S  O  R  E  S        D  E        E  S  T  E     Y     O  E  S  T  E*/


    	/*P A R A        E S e n s o r  ==  1  & &   W S e n s o r ==  0 */

    	case 19:												//Estado Rojo (NS-SN)/ Verde EO / Verde Parpadeo OE, t=1s
    		actual_state=estado;
    		do{
    			TPM_SetTimerPeriod(TPM1, 64u);
    			TPM_StartTimer(TPM1, kTPM_SystemClock);
    			GPIO_TogglePinsOutput(GPIOA, 1u<<4u);
    			while(!(TPM1->STATUS & Mask)){			//Wait
    			}

    			if(TPM1->STATUS & Mask){
    				TPM1->STATUS &= Mask_Off;
    				Counter=Counter+1;
    				TPM_StopTimer(TPM1);
    				TPM1->CNT=0;
    			}
    		}while(Counter<=9);
    		Counter=0;
    		estado=20;
    	break;

    	case 20:											//Estado Verde EO / Amarillo OE / Rojo (NS-SN), t=2s								S e  c u m p l e n  l o s  10 s
    		actual_state=estado;
    		if(Timer_init==0){
    			Timer_init=1;
    			TPM_SetTimerPeriod(TPM0, FSM[20].TIMER_MOD);
    			TPM_StartTimer(TPM0, kTPM_SystemClock);
    		}

    		if(TIMER_FLAG){
    			TPM_ClearStatusFlags(TPM0, 1u<<8u);
    			Timer_init= 0;
    			TPM_StopTimer(TPM0);
    			TPM0->CNT=0;
    			estado= 21;
    		}
    	break;

    	case 21:											//Estado Verde y Vuelta EO / Rojo OE / Rojo (NS-SN), t=4s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[21].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 22;
			}
    	break;

    	case 22:											//Estado Verde y Vuelta Parpadeo EO / Rojo OE / Rojo (NS-SN), t=1s
    		actual_state=estado;
    		do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOC, 1u<<5u);
				GPIO_TogglePinsOutput(GPIOC, 1u<<0u);
				while(!(TPM1->STATUS & Mask)){			//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &= Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}
			}while(Counter<=9);
			Counter=0;
			estado=23;
		break;

    	case 23:											//Estado Amarillo EO / Rojo OE / Rojo (NS-SN), t=2s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[23].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 1;
			}
    	break;


    	/*P A R A        E S e n s o r  ==  0  & &   W S e n s o r ==  1 */

    	case 24:												//Estado Verde Parpadeo EO / Verde OE / Rojo (NS-SN), t=1s
    		actual_state=estado;
    		do{
    			TPM_SetTimerPeriod(TPM1, 64u);
    			TPM_StartTimer(TPM1, kTPM_SystemClock);
    			GPIO_TogglePinsOutput(GPIOC, 1u<<5u);
    			while(!(TPM1->STATUS & Mask)){			//Wait
    			}

    			if(TPM1->STATUS & Mask){
    				TPM1->STATUS &= Mask_Off;
    				Counter=Counter+1;
    				TPM_StopTimer(TPM1);
    				TPM1->CNT=0;
    			}
    		}while(Counter<=9);
    		Counter=0;
    		estado=25;
    	break;

    	case 25:											//Estado Amarillo EO / Verde OE / Rojo (NS-SN), t=2s								S e  c u m p l e n  l o s  10 s
    		actual_state=estado;
    		if(Timer_init==0){
    			Timer_init=1;
    			TPM_SetTimerPeriod(TPM0, FSM[25].TIMER_MOD);
    			TPM_StartTimer(TPM0, kTPM_SystemClock);
    		}

    		if(TIMER_FLAG){
    			TPM_ClearStatusFlags(TPM0, 1u<<8u);
    			Timer_init= 0;
    			TPM_StopTimer(TPM0);
    			TPM0->CNT=0;
    			estado= 26;
    		}
    	break;

    	case 26:											//Estado Rojo EO / Verde y Vuelta OE / Rojo (NS-SN), t=4s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[16].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 27;
			}
    	break;

    	case 27:											//Estado Rojo EO / Verde y Vuelta Parpadeo OE / Rojo (NS-SN), t=1s
    		actual_state=estado;
    		do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOA, 1u<<4u);
				GPIO_TogglePinsOutput(GPIOA, 1u<<2u);
				while(!(TPM1->STATUS & Mask)){			//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &= Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}
			}while(Counter<=9);
			Counter=0;
			estado=28;
		break;

    	case 28:											//Estado Rojo EO / Amarillo OE / Rojo (NS-SN), t=2s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[28].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 1;
			}
    	break;

    	/*P A R A        N S e n s o r  ==  1  & &   S S e n s o r ==  1 */

    	case 29:											//Estado Azul (NS-SN), Rojo (NS-SN-EO-OE), t=4s
    		actual_state=estado;
    		if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[29].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 30;
			}
    	break;

    	case 30:										//Estado Parpadeo Azul (NS-SN), Rojo (NS-SN-EO-OE), t=1s
    		actual_state=estado;
    		do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOB, 1u<<3u);
				GPIO_TogglePinsOutput(GPIOE, 1u<<23u);
				while(!(TPM1->STATUS & Mask)){			//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &= Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}
			}while(Counter<=9);
			Counter=0;
			estado_reg=0;
			estado=4;
    	break;



		/*P A R A        E S e n s o r  ==  1  & &   W S e n s o r ==  1 */


    	case 31:											//Estado Azul (EO-OE), Rojo (NS-SN-EO-OE), t=4s
    		actual_state=estado;
			if(Timer_init==0){
				Timer_init=1;
				TPM_SetTimerPeriod(TPM0, FSM[31].TIMER_MOD);
				TPM_StartTimer(TPM0, kTPM_SystemClock);
			}

			if(TIMER_FLAG){
				TPM_ClearStatusFlags(TPM0, 1u<<8u);
				Timer_init= 0;
				TPM_StopTimer(TPM0);
				TPM0->CNT=0;
				estado= 32;
			}
		break;

		case 32:										//Estado Parpadeo Azul (EO-OE), Rojo (NS-SN-EO-OE), t=1s
			actual_state=estado;
			do{
				TPM_SetTimerPeriod(TPM1, 64u);
				TPM_StartTimer(TPM1, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOC, 1u<<0u);
				GPIO_TogglePinsOutput(GPIOA, 1u<<2u);
				while(!(TPM1->STATUS & Mask)){			//Wait
				}

				if(TPM1->STATUS & Mask){
					TPM1->STATUS &= Mask_Off;
					Counter=Counter+1;
					TPM_StopTimer(TPM1);
					TPM1->CNT=0;
				}
			}while(Counter<=9);
			Counter=0;
			estado_reg=0;
			estado=8;
		break;



    	case 33:
    		GPIO_WritePinOutput(GPIOB, NGreen, FSM[estado].NVerde);
			GPIO_WritePinOutput(GPIOB, NYellow, FSM[estado].NAmarillo);
			GPIO_WritePinOutput(GPIOB, NRed, FSM[estado].NRojo);
			GPIO_WritePinOutput(GPIOB, NBlue, FSM[estado].NAzul);
			GPIO_WritePinOutput(GPIOE, SGreen, FSM[estado].SVerde);
			GPIO_WritePinOutput(GPIOE, SYellow, FSM[estado].SAmarillo);
			GPIO_WritePinOutput(GPIOE, SRed, FSM[estado].SRojo);
			GPIO_WritePinOutput(GPIOE, SBlue, FSM[estado].SAzul);
			GPIO_WritePinOutput(GPIOC, EGreen, FSM[estado].EVerde);
			GPIO_WritePinOutput(GPIOC, EYellow, FSM[estado].EAmarillo);
			GPIO_WritePinOutput(GPIOC, ERed, FSM[estado].ERojo);
			GPIO_WritePinOutput(GPIOC, EBlue, FSM[estado].EAzul);
			GPIO_WritePinOutput(GPIOA, WGreen, FSM[estado].OVerde);
			GPIO_WritePinOutput(GPIOA, WYellow, FSM[estado].OAmarillo);
			GPIO_WritePinOutput(GPIOD, WRed, FSM[estado].ORojo);
			GPIO_WritePinOutput(GPIOC, WBlue, FSM[estado].OAzul);

    		do{

    			TPM_SetTimerPeriod(TPM2, 16u);
				TPM_StartTimer(TPM2, kTPM_SystemClock);
				GPIO_TogglePinsOutput(GPIOB, 1u<<1u);
				GPIO_TogglePinsOutput(GPIOE, 1u<<21u);
				GPIO_TogglePinsOutput(GPIOC, 1u<<4u);
				GPIO_TogglePinsOutput(GPIOA, 1u<<12u);
				while(!(TPM2->STATUS & Mask2)){ 		//Wait
				}

				if(TPM2->STATUS & Mask2){
					TPM2->STATUS &=Mask_Off2;
					Counter=Counter+1;
					TPM_StopTimer(TPM2);
					TPM2->CNT=0;
				}

			}while(Counter<=9);
    		estado=actual_state;

    	break;

    	}
    }

}
