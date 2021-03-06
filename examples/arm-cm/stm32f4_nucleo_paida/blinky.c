/*.$file${.::blinky.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: dpp.qm
* File:  ${.::blinky.c}
*
* This code has been generated by QM 5.1.1 <www.state-machine.com/qm/>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*.$endhead${.::blinky.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
 #include "qpc.h"
 #include "blinky.h"
 #include "bsp.h"

 Q_DEFINE_THIS_FILE

 /* Active object class -----------------------------------------------------*/
 /*.$declare${AOs::Blinky} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${AOs::Blinky} ..........................................................*/
typedef struct {
/* protected: */
    QActive super;

/* private: */
    QTimeEvt timeEvt;
} Blinky;

/* protected: */
static QState Blinky_initial(Blinky * const me, void const * const par);
static QState Blinky_off(Blinky * const me, QEvt const * const e);
static QState Blinky_on(Blinky * const me, QEvt const * const e);
/*.$enddecl${AOs::Blinky} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/


 #define FREE      ((uint8_t)0)
 #define USED      ((uint8_t)1)

 /* Local objects -----------------------------------------------------------*/
 static Blinky blinks; /* the single instance of the Table active object */

 /* Global-scope objects ----------------------------------------------------*/
 QActive * const AO_Blinky = &blinks.super; /* "opaque" AO pointer */

 /*..........................................................................*/
 /*.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*. Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.9.0 or higher required
#endif
/*.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$define${AOs::blinky_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${AOs::blinky_ctor} .....................................................*/
void blinky_ctor(void) {
    Blinky *me = (Blinky *)AO_Blinky;
    QActive_ctor(&me->super,Q_STATE_CAST(&Blinky_initial));
    QTimeEvt_ctorX(&me->timeEvt,&me->super,TIMEOUT_SIG,0U);
}
/*.$enddef${AOs::blinky_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
 /*.$define${AOs::Blinky} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${AOs::Blinky} ..........................................................*/
/*.${AOs::Blinky::SM} ......................................................*/
static QState Blinky_initial(Blinky * const me, void const * const par) {
    /*.${AOs::Blinky::SM::initial} */
    QTimeEvt_armX(&me->timeEvt,
        BSP_TICKS_PER_SEC/3,
        BSP_TICKS_PER_SEC);
    return Q_TRAN(&Blinky_off);
}
/*.${AOs::Blinky::SM::off} .................................................*/
static QState Blinky_off(Blinky * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::Blinky::SM::off} */
        case Q_ENTRY_SIG: {
            BSP_ledoff();

            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::Blinky::SM::off::TIMEOUT} */
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&Blinky_on);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.${AOs::Blinky::SM::on} ..................................................*/
static QState Blinky_on(Blinky * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*.${AOs::Blinky::SM::on} */
        case Q_ENTRY_SIG: {
            BSP_ledon();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::Blinky::SM::on::TIMEOUT} */
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&Blinky_off);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.$enddef${AOs::Blinky} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
