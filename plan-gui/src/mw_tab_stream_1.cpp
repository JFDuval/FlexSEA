//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Stream 1 (Execute)
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <string>

void MainWindow::init_tab_stream_execute(void)
{
    fake_data = 0;
}

void MainWindow::stream_execute(void)
{
    int numb = 0;
    struct execute_s *ex_ptr;

    numb = tx_cmd_data_read_all(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN); //New Read All function
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    numb = COMM_STR_BUF_LEN;

    USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

    //Can we decode what we received?
    USBSerialPort_Read(usb_rx);
    decode_usb_rx(usb_rx);

    //Refresh display:
    assign_execute_ptr(&ex_ptr, active_slave_1_index);
    disp_execute(ex_ptr, 0);
}

void MainWindow::disp_execute(struct execute_s *ex, uint8_t slave_ab)
{
    int combined_status = 0;

    if(slave_ab == 0)
    {
        //Raw values:
        //===========

        ui->disp_accx->setText(QString::number(ex->accel.x));
        ui->disp_accy->setText(QString::number(ex->accel.y));
        ui->disp_accz->setText(QString::number(ex->accel.z));
        ui->disp_gyrox->setText(QString::number(ex->gyro.x));
        ui->disp_gyroy->setText(QString::number(ex->gyro.y));
        ui->disp_gyroz->setText(QString::number(ex->gyro.z));

        ui->disp_enc->setText(QString::number(ex->enc_display));

        ui->disp_strain->setText(QString::number(ex->strain));
        ui->disp_ana->setText(QString::number(ex->analog[0]));
        ui->disp_ana1->setText(QString::number(ex->analog[1]));

        ui->disp_current->setText(QString::number(ex->current));

        ui->disp_vb->setText(QString::number(ex->volt_batt));
        ui->disp_vg->setText(QString::number(ex->volt_int));
        ui->disp_temp->setText(QString::number(ex->temp));

        combined_status = (ex->status2 << 8) & ex->status1;
        ui->disp_stat1->setText(QString::number(combined_status));

        //Decode some of them:
        //===================

        ui->disp_current_d->setText(QString::number((float)ex->current*18.5, 'i',0));
        ui->disp_vb_d->setText(QString::number(P4_ADC_SUPPLY*((16*(float)ex->volt_batt/3 + 302 )/P4_ADC_MAX) / 0.0738, 'f',2));
        ui->disp_vg_d->setText(QString::number(P4_ADC_SUPPLY*((26*(float)ex->volt_int/3 + 440 )/P4_ADC_MAX) / 0.43, 'f',2));
        ui->disp_temp_d->setText(QString::number(((((2.625*(float)ex->temp + 41)/P4_ADC_MAX)*P4_ADC_SUPPLY) - P4_T0) / P4_TC,'f',1));

        ui->disp_ana_d->setText(QString::number(((float)ex->analog[0]/P5_ADC_MAX)*P5_ADC_SUPPLY,'f',2));
        ui->disp_ana1_d->setText(QString::number(((float)ex->analog[1]/P5_ADC_MAX)*P5_ADC_SUPPLY,'f',2));

        ui->disp_accx_d->setText(QString::number((double)ex->accel.x/8192, 'f', 2));
        ui->disp_accy_d->setText(QString::number((double)ex->accel.y/8192, 'f', 2));
        ui->disp_accz_d->setText(QString::number((double)ex->accel.z/8192, 'f', 2));
        ui->disp_gyrox_d->setText(QString::number((double)ex->gyro.x/16.4, 'i', 0));
        ui->disp_gyroy_d->setText(QString::number((double)ex->gyro.y/16.4, 'i', 0));
        ui->disp_gyroz_d->setText(QString::number((double)ex->gyro.z/16.4, 'i', 0));

        ui->disp_strain_d->setText(QString::number(((double)(ex->strain-32768)/32768)*100, 'i', 0));

        status_byte_disp(ex->status1, ex->status2, 0);

        ui->tabWidget->repaint();

        //==========
    }
    else
    {

    }
}

#define GET_WDCLK_FLAG(status1) ((status1 >> 7) & 0x01)
#define GET_DISCON_FLAG(status1) ((status1 >> 6) & 0x01)
#define GET_OVERTEMP_FLAG(status1) ((status1 >> 4) & 0x03)
#define GET_VB_FLAG(status1) ((status1 >> 2) & 0x03)
#define GET_VG_FLAG(status1) ((status1 >> 0) & 0x03)
#define GET_3V3_FLAG(status2) ((status2 >> 0) & 0x03)
#define GET_FSM_FLAG(status2) ((status2 >> 7) & 0x01)

//Qualitative:
#define V_LOW				1
#define V_NORMAL			0
#define V_HIGH				2
#define T_NORMAL			0
#define T_WARNING			1
#define T_ERROR				2
#define BATT_CONNECTED		0
#define BATT_DISCONNECTED	1
//If everything is normal STATUS1 == 0

void MainWindow::status_byte_disp(uint8_t stat1, uint8_t stat2, uint8_t slave_ab)
{
    QString str1;
    uint8_t mod = 0;

    //Status 1:
    //==========

    //WDCLK:
    if(GET_WDCLK_FLAG(stat1))
    {
        str1 += QString("Co-Processor Error");
        mod++;
    }

    //Disconnected battery:
    if(GET_DISCON_FLAG(stat1) == BATT_DISCONNECTED)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("Disconnected battery");
        mod++;
    }

    //Temperature:
    if(GET_OVERTEMP_FLAG(stat1) == T_WARNING)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("Temp. Near Limit");
        mod++;
    }
    else if(GET_OVERTEMP_FLAG(stat1) == T_ERROR)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("Temp. Error");
        mod++;
    }

    //Voltage - VB:
    if(GET_VB_FLAG(stat1) == V_LOW)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("VB Low");
        mod++;
    }
    else if(GET_VB_FLAG(stat1) == V_HIGH)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("VB High");
        mod++;
    }

    //Voltage - VG:
    if(GET_VG_FLAG(stat1) == V_LOW)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("VG Low");
        mod++;
    }
    else if(GET_VG_FLAG(stat1) == V_HIGH)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("VG High");
        mod++;
    }

    //Status 2:
    //==========

    //FSM:
    if(GET_FSM_FLAG(stat2) == 1)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("FSM Enabled");
        mod++;
    }

    //Voltage - 3V3:
    if(GET_3V3_FLAG(stat2) == V_LOW)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("3V3 Low");
        mod++;
    }
    else if(GET_3V3_FLAG(stat2) == V_HIGH)
    {
        if(mod){str1 += QString(" | ");};
        str1 += QString("3V3 High");
        mod++;
    }

    //If nothing is wrong:
    if(mod == 0)
    {
        str1 = QString("Status: OK");
    }

    //Display string:
    if(slave_ab == 0)
    {
        ui->label_status1->setText(str1);
    }
    else if(slave_ab == 1)
    {
        ui->label_status1_2->setText(str1);
    }
}

void MainWindow::disp_slave_a(bool enable)
{
    ui->disp_accx->setEnabled(enable);
    ui->disp_accy->setEnabled(enable);
    ui->disp_accz->setEnabled(enable);
    ui->disp_gyrox->setEnabled(enable);
    ui->disp_gyroy->setEnabled(enable);
    ui->disp_gyroz->setEnabled(enable);

    ui->disp_enc->setEnabled(enable);

    ui->disp_strain->setEnabled(enable);
    ui->disp_ana->setEnabled(enable);
    ui->disp_ana1->setEnabled(enable);

    ui->disp_current->setEnabled(enable);

    ui->disp_vb->setEnabled(enable);
    ui->disp_vg->setEnabled(enable);
    ui->disp_temp->setEnabled(enable);

    ui->disp_stat1->setEnabled(enable);
    ui->label_status1->setEnabled(enable);

    ui->disp_current_d->setEnabled(enable);
    ui->disp_vb_d->setEnabled(enable);
    ui->disp_vg_d->setEnabled(enable);
    ui->disp_temp_d->setEnabled(enable);

    ui->disp_ana_d->setEnabled(enable);
    ui->disp_ana1_d->setEnabled(enable);

    ui->disp_accx_d->setEnabled(enable);
    ui->disp_accy_d->setEnabled(enable);
    ui->disp_accz_d->setEnabled(enable);
    ui->disp_gyrox_d->setEnabled(enable);
    ui->disp_gyroy_d->setEnabled(enable);
    ui->disp_gyroz_d->setEnabled(enable);

    ui->disp_strain_d->setEnabled(enable);
}

void MainWindow::disp_slave_b(bool enable)
{
    ui->disp_accx_2->setEnabled(enable);
    ui->disp_accy_2->setEnabled(enable);
    ui->disp_accz_2->setEnabled(enable);
    ui->disp_gyrox_2->setEnabled(enable);
    ui->disp_gyroy_2->setEnabled(enable);
    ui->disp_gyroz_2->setEnabled(enable);

    ui->disp_enc_2->setEnabled(enable);

    ui->disp_strain_2->setEnabled(enable);
    ui->disp_ana_2->setEnabled(enable);
    ui->disp_ana1_2->setEnabled(enable);

    ui->disp_current_2->setEnabled(enable);

    ui->disp_vb_2->setEnabled(enable);
    ui->disp_vg_2->setEnabled(enable);
    ui->disp_temp_2->setEnabled(enable);

    ui->disp_stat1_2->setEnabled(enable);
    ui->label_status1_2->setEnabled(enable);

    ui->disp_current_d_2->setEnabled(enable);
    ui->disp_vb_d_2->setEnabled(enable);
    ui->disp_vg_d_2->setEnabled(enable);
    ui->disp_temp_d_2->setEnabled(enable);

    ui->disp_ana_d_2->setEnabled(enable);
    ui->disp_ana1_d_2->setEnabled(enable);

    ui->disp_accx_d_2->setEnabled(enable);
    ui->disp_accy_d_2->setEnabled(enable);
    ui->disp_accz_d_2->setEnabled(enable);
    ui->disp_gyrox_d_2->setEnabled(enable);
    ui->disp_gyroy_d_2->setEnabled(enable);
    ui->disp_gyroz_d_2->setEnabled(enable);

    ui->disp_strain_d_2->setEnabled(enable);
}
