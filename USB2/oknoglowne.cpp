//int size;
//        unsigned char datain[1024]="\0";
//       for(int i=0;i<30;i++)
//        {
//            int rr = libusb_bulk_transfer(dev_handle,
//                    0x81,
//                    datain,
//                    0x0004,
//                    &size,
//                    1000);
//            qDebug()<<"libusb_bulk_transfer rr: "<<rr<<endl;
//            qDebug()<<"size: "<<size<<endl;
//            qDebug()<<"data: ";
//            for(int j=0; j<size; j++)
//                 qDebug()<<"%02x ", (unsigned char)(datain[j]);
//            qDebug()<<"\n";
//        }
//}

