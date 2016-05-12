//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
//****************************************************************************
// MainWindow: Qt GUI Main file - tab:Stream 3 (Strain Amp)
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

void MainWindow::on_stream_SA_ONbutto_clicked()
{
	ui->stream_SA_ONbutto->setDisabled(1);
	ui->stream_SA_OFFbutton->setEnabled(1);

	ui->stream_SA_ONbutto->repaint();
	ui->stream_SA_OFFbutton->repaint();

	stream_status = 0;	//Can't have 2 stream at the same time
	stream_sa_status = 1;
}

void MainWindow::on_stream_SA_OFFbutton_clicked()
{
	ui->stream_SA_ONbutto->setEnabled(1);
	ui->stream_SA_OFFbutton->setDisabled(1);

	ui->stream_SA_ONbutto->repaint();
	ui->stream_SA_OFFbutton->repaint();

	stream_status = 0;	//Can't have 2 stream at the same time
    stream_sa_status = 0;
}

void MainWindow::on_stream_SA_RefreshOffset_clicked()
{
	uint8_t offs[6] = {0,0,0,0,0,0};

	//Read, bound, and update display with the correct value (if needed)
	offs[0] = bound_number(ui->strain_offs_ch1->text().toInt(), 0, 255);
	offs[1] = bound_number(ui->strain_offs_ch2->text().toInt(), 0, 255);
	offs[2] = bound_number(ui->strain_offs_ch3->text().toInt(), 0, 255);
	offs[3] = bound_number(ui->strain_offs_ch4->text().toInt(), 0, 255);
	offs[4] = bound_number(ui->strain_offs_ch5->text().toInt(), 0, 255);
	offs[5] = bound_number(ui->strain_offs_ch6->text().toInt(), 0, 255);
    ui->strain_offs_ch1->setText(QString::number(offs[0]));
    ui->strain_offs_ch2->setText(QString::number(offs[1]));
    ui->strain_offs_ch3->setText(QString::number(offs[2]));
    ui->strain_offs_ch4->setText(QString::number(offs[3]));
    ui->strain_offs_ch5->setText(QString::number(offs[4]));
    ui->strain_offs_ch6->setText(QString::number(offs[5]));

    qDebug() << "Offsets: [" << offs[0] << "," << offs[1] << "," << offs[2] << "," \
             << offs[3] << "," << offs[4] << "," << offs[5] << "].";
	qDebug() << "ToDo: send an actual command!";
}

void MainWindow::timerStream_SA_Event(void)
{
    if(stream_sa_status)
    {
        //==========
        //Test: call STRAIN

        int numb = 0;

        numb = tx_cmd_strain(active_slave_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);
        numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;

        //flexsea_serial_transmit(numb, comm_str_spi, 0); //DIY driver
        USBSerialPort_Write(numb, comm_str_usb);        //QSerialPort

        //Can we decode what we received?
        USBSerialPort_Read(usb_rx);
        decode_usb_rx(usb_rx);

        //Raw values:
        ui->disp_strain_ch1->setText(QString::number(strain[0].strain_filtered));
        ui->disp_strain_ch2->setText(QString::number(strain[1].strain_filtered));
        ui->disp_strain_ch3->setText(QString::number(strain[2].strain_filtered));
        ui->disp_strain_ch4->setText(QString::number(strain[3].strain_filtered));
        ui->disp_strain_ch5->setText(QString::number(strain[4].strain_filtered));
        ui->disp_strain_ch6->setText(QString::number(strain[5].strain_filtered));

            //Decode some of them:
            //===================

        ui->disp_strain_ch1_d->setText(QString::number(((double)(strain[0].strain_filtered-32768)/32768)*100, 'i', 0));
        ui->disp_strain_ch2_d->setText(QString::number(((double)(strain[1].strain_filtered-32768)/32768)*100, 'i', 0));
        ui->disp_strain_ch3_d->setText(QString::number(((double)(strain[2].strain_filtered-32768)/32768)*100, 'i', 0));
        ui->disp_strain_ch4_d->setText(QString::number(((double)(strain[3].strain_filtered-32768)/32768)*100, 'i', 0));
        ui->disp_strain_ch5_d->setText(QString::number(((double)(strain[4].strain_filtered-32768)/32768)*100, 'i', 0));
        ui->disp_strain_ch6_d->setText(QString::number(((double)(strain[5].strain_filtered-32768)/32768)*100, 'i', 0));

        ui->tabWidget->repaint();

        //==========
    }
}

//Makes sure that num is between the min/max boundaries.
uint8_t MainWindow::bound_number(int num, int min, int max)
{
	if(num < min)
		return min;
	if(num > max)
		return max;

	return num;
}

