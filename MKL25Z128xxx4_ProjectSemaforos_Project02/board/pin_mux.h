/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*! @name PORTB0 (number 43), J10[2]/A0
  @{ */
#define BOARD_INITPINS_NGreen_FGPIO FGPIOB /*!<@brief FGPIO device name: FGPIOB */
#define BOARD_INITPINS_NGreen_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_NGreen_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_NGreen_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                         /* @} */

/*! @name PORTB1 (number 44), J10[4]/A1
  @{ */
#define BOARD_INITPINS_NYellow_FGPIO FGPIOB /*!<@brief FGPIO device name: FGPIOB */
#define BOARD_INITPINS_NYellow_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_NYellow_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_NYellow_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                          /* @} */

/*! @name PORTB2 (number 45), J10[6]/A2
  @{ */
#define BOARD_INITPINS_NRed_FGPIO FGPIOB /*!<@brief FGPIO device name: FGPIOB */
#define BOARD_INITPINS_NRed_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_NRed_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_NRed_PIN 2U     /*!<@brief PORTB pin index: 2 */
                                       /* @} */

/*! @name PORTB3 (number 46), J10[8]/A3
  @{ */
#define BOARD_INITPINS_NBlue_FGPIO FGPIOB /*!<@brief FGPIO device name: FGPIOB */
#define BOARD_INITPINS_NBlue_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_NBlue_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_NBlue_PIN 3U     /*!<@brief PORTB pin index: 3 */
                                        /* @} */

/*! @name PORTC2 (number 57), J10[10]/A4
  @{ */
#define BOARD_INITPINS_NSense_FGPIO FGPIOC /*!<@brief FGPIO device name: FGPIOC */
#define BOARD_INITPINS_NSense_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_NSense_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_NSense_PIN 2U     /*!<@brief PORTC pin index: 2 */
                                         /* @} */

/*! @name PORTE20 (number 13), J10[1]
  @{ */
#define BOARD_INITPINS_SGreen_FGPIO FGPIOE /*!<@brief FGPIO device name: FGPIOE */
#define BOARD_INITPINS_SGreen_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_SGreen_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_SGreen_PIN 20U    /*!<@brief PORTE pin index: 20 */
                                         /* @} */

/*! @name PORTE21 (number 14), J10[3]
  @{ */
#define BOARD_INITPINS_SYellow_FGPIO FGPIOE /*!<@brief FGPIO device name: FGPIOE */
#define BOARD_INITPINS_SYellow_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_SYellow_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_SYellow_PIN 21U    /*!<@brief PORTE pin index: 21 */
                                          /* @} */

/*! @name PORTE22 (number 15), J10[5]
  @{ */
#define BOARD_INITPINS_SRed_FGPIO FGPIOE /*!<@brief FGPIO device name: FGPIOE */
#define BOARD_INITPINS_SRed_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_SRed_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_SRed_PIN 22U    /*!<@brief PORTE pin index: 22 */
                                       /* @} */

/*! @name PORTE23 (number 16), J10[7]
  @{ */
#define BOARD_INITPINS_SBlue_FGPIO FGPIOE /*!<@brief FGPIO device name: FGPIOE */
#define BOARD_INITPINS_SBlue_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_SBlue_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_SBlue_PIN 23U    /*!<@brief PORTE pin index: 23 */
                                        /* @} */

/*! @name PORTE29 (number 21), J10[9]
  @{ */
#define BOARD_INITPINS_SSense_FGPIO FGPIOE /*!<@brief FGPIO device name: FGPIOE */
#define BOARD_INITPINS_SSense_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_INITPINS_SSense_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_SSense_PIN 29U    /*!<@brief PORTE pin index: 29 */
                                         /* @} */

/*! @name PORTC5 (number 62), J1[9]
  @{ */
#define BOARD_INITPINS_EGreen_FGPIO FGPIOC /*!<@brief FGPIO device name: FGPIOC */
#define BOARD_INITPINS_EGreen_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_EGreen_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_EGreen_PIN 5U     /*!<@brief PORTC pin index: 5 */
                                         /* @} */

/*! @name PORTC4 (number 61), J1[7]
  @{ */
#define BOARD_INITPINS_EYellow_FGPIO FGPIOC /*!<@brief FGPIO device name: FGPIOC */
#define BOARD_INITPINS_EYellow_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_EYellow_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_EYellow_PIN 4U     /*!<@brief PORTC pin index: 4 */
                                          /* @} */

/*! @name PORTC3 (number 58), J1[5]
  @{ */
#define BOARD_INITPINS_ERed_FGPIO FGPIOC /*!<@brief FGPIO device name: FGPIOC */
#define BOARD_INITPINS_ERed_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_ERed_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_ERed_PIN 3U     /*!<@brief PORTC pin index: 3 */
                                       /* @} */

/*! @name PORTC0 (number 55), J1[3]
  @{ */
#define BOARD_INITPINS_EBlue_FGPIO FGPIOC /*!<@brief FGPIO device name: FGPIOC */
#define BOARD_INITPINS_EBlue_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_EBlue_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_EBlue_PIN 0U     /*!<@brief PORTC pin index: 0 */
                                        /* @} */

/*! @name PORTC7 (number 64), J1[1]
  @{ */
#define BOARD_INITPINS_ESense_FGPIO FGPIOC /*!<@brief FGPIO device name: FGPIOC */
#define BOARD_INITPINS_ESense_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_ESense_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_ESense_PIN 7U     /*!<@brief PORTC pin index: 7 */
                                         /* @} */

/*! @name PORTA4 (number 30), J1[10]/D4
  @{ */
#define BOARD_INITPINS_WGreen_FGPIO FGPIOA /*!<@brief FGPIO device name: FGPIOA */
#define BOARD_INITPINS_WGreen_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_WGreen_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_WGreen_PIN 4U     /*!<@brief PORTA pin index: 4 */
                                         /* @} */

/*! @name PORTA12 (number 32), J1[8]/D3
  @{ */
#define BOARD_INITPINS_WYellow_FGPIO FGPIOA /*!<@brief FGPIO device name: FGPIOA */
#define BOARD_INITPINS_WYellow_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_WYellow_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_WYellow_PIN 12U    /*!<@brief PORTA pin index: 12 */
                                          /* @} */

/*! @name PORTD4 (number 77), J1[6]/D2
  @{ */
#define BOARD_INITPINS_WRed_FGPIO FGPIOD /*!<@brief FGPIO device name: FGPIOD */
#define BOARD_INITPINS_WRed_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_WRed_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_WRed_PIN 4U     /*!<@brief PORTD pin index: 4 */
                                       /* @} */

/*! @name PORTA13 (number 33), J2[2]/D8
  @{ */
#define BOARD_INITPINS_PeopleSense_FGPIO FGPIOA /*!<@brief FGPIO device name: FGPIOA */
#define BOARD_INITPINS_PeopleSense_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_PeopleSense_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_PeopleSense_PIN 13U    /*!<@brief PORTA pin index: 13 */
                                              /* @} */

/*! @name PORTA1 (number 27), J1[2]/D0/UART0_RX
  @{ */
#define BOARD_INITPINS_WSense_FGPIO FGPIOA /*!<@brief FGPIO device name: FGPIOA */
#define BOARD_INITPINS_WSense_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_WSense_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_WSense_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                         /* @} */

/*! @name PORTA2 (number 28), J1[4]/D1/UART0_TX
  @{ */
#define BOARD_INITPINS_WBlue_FGPIO FGPIOA /*!<@brief FGPIO device name: FGPIOA */
#define BOARD_INITPINS_WBlue_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_WBlue_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_WBlue_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                        /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
