/*
  Author : Mohamed Abd Elnaser & Mohamed Abd Elmotaal
  Release : V 1.0.0
  Type   : I2C communiction protocol Driver 
	                                           */

#include "TM4C123GH6PM.h"
#include "TM4C123GH6PM_I2C_INTERFACE.h"
#include <stdint.h>

/*****************************************************************
**********Describtion : initilization the i2c*********************
             Required : 1- i2c_module_num you want to use(0,1,2,3)
                       	2- I2C_MODE {MASTER,SLAVE}						
***************return : void *************************************/
void I2C_init(int8_t I2C_NUM ,uint8_t I2C_MODE)
{
	switch(I2C_NUM)
	{
		case 0:
      SYSCTL->RCGCI2C |= I2C0_CE;                /* enable clock to I2C */
      I2C0->MTPR = TPR;                    /*ex: I2C_CLK speed using here is 100 kHz @ 16 MHz  */
      I2C0->MCR = I2C_MODE;                /* The mode you want  MASTER or SLAVE   */
      break;		
		case 1:
      SYSCTL->RCGCI2C |= I2C1_CE;                /* enable clock to I2C */
      I2C1->MTPR = TPR;                    /*ex: I2C_CLK speed using here is 100 kHz @ 16 MHz  */
      I2C1->MCR = I2C_MODE;                 /* The mode you want  MASTER or SLAVE   */
		  break;
		case 2:
      SYSCTL->RCGCI2C |= I2C2_CE;                /* enable clock to I2C */
      I2C2->MTPR = TPR;                    /*ex: I2C_CLK speed using here is 100 kHz @ 16 MHz  */
      I2C2->MCR = I2C_MODE;                  /* The mode you want  MASTER or SLAVE   */
		  break;
		case 3:
      SYSCTL->RCGCI2C |= I2C3_CE;                /* enable clock to I2C */
      I2C3->MTPR = TPR;                    /*ex: I2C_CLK speed using here is 100 kHz @ 16 MHz  */
      I2C3->MCR = I2C_MODE;                 /* The mode you want  MASTER or SLAVE   */
      break;
	}
}	
/************************************************************
*****Describtion : making sure that i2c master is not busy
                 and  no error ,ack_add is recived 
                 and  ack_data (first address ) is recived 
        
        Required : i2c_module_num you want to use(0,1,2,3)

*******Return : 8_bit variable erorr if this a problem *******
                   or zero (0) if evrey thing is okay 
*************************************************************/
static int8_t I2C_wait_till_done(int8_t I2C_NUM)
{
	switch(I2C_NUM)
	{
		case 0:
      while( I2C0->MCS & 1);      /* wait until I2C master is not busy */
      return I2C0->MCS & 0xE;    /* return I2C error code */
		  break;
		
		case 1:
      while( I2C1->MCS & 1);      /* wait until I2C master is not busy */
      return I2C1->MCS & 0xE;    /* return I2C error code */
		  break;
		
		case 2:
      while( I2C2->MCS & 1);      /* wait until I2C master is not busy */
      return I2C2->MCS & 0xE;    /* return I2C error code */
		  break;
		
		case 3:
      while( I2C3->MCS & 1);      /* wait until I2C master is not busy */
      return I2C3->MCS & 0xE;    /* return I2C error code */
      break;
	}

}

/*******************************************************************
***********Describtion : Write one byte only ***********************

*******      Required  : 1-i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3- memory addres location of the data you want
                         4- pointer to save the reading data 

***** byte write seq : S-(saddr+w)-ACK-maddr-ACK-data-ACK-P *********
         
** return : 8_bit variable erorr if this a problem ******************
            or zero (0) if evrey thing is okay
*********************************************************************/

uint8_t I2C_byteWrite(int8_t I2C_NUM ,int8_t slaveAddr, int8_t memAddr, uint8_t data)
{
uint8_t error;
	switch(I2C_NUM)
	{
		case 0:
        /* send slave address and starting address to their regestiers  */
        I2C0->MSA = slaveAddr << 1;
        I2C0->MDR = memAddr;
	
        /*starting writing seq whic is  
	        S-(saddr+w)-ACK-maddr-ACK */
        I2C0->MCS = 3; 
        error = I2C_wait_till_done(0);        /* wait until write is complete */
        if (error) return error;
	
        /* sending data and waiting for ack and then sending stop */
        I2C0->MDR = data;                     /* loading data  in data reg*/
        I2C0->MCS = 5;                        /* -data-ACK-P */
        /*error = I2C_wait_till_done(0);*/    /*this line not working (checking ack_address)      /* wait until write is complete */
        while(I2C0->MCS & 0x40);              /* wait until bus is not busy */
        error = I2C0->MCS & 0xA;              /*checking that there are no error and ack_data is recived */ 
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;
		
		case 1:
        /* send slave address and starting address to their regestiers  */
        I2C1->MSA = slaveAddr << 1;
        I2C1->MDR = memAddr;
	
        /*starting writing seq whic is  
	        S-(saddr+w)-ACK-maddr-ACK */
        I2C1->MCS = 3; 
        error = I2C_wait_till_done(1);        /* wait until write is complete */
        if (error) return error;
	
        /* sending data and waiting for ack and then sending stop */
        I2C1->MDR = data;                     /* loading data  in data reg*/
        I2C1->MCS = 5;                        /* -data-ACK-P */
        /*error = I2C_wait_till_done(1);*/    /*this line not working (checking ack_address)      /* wait until write is complete */
        while(I2C1->MCS & 0x40);              /* wait until bus is not busy */
        error = I2C1->MCS & 0xA;              /*checking that there are no error and ack_data is recived */ 
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;
		
		case 2:
        /* send slave address and starting address to their regestiers  */
        I2C2->MSA = slaveAddr << 1;
        I2C2->MDR = memAddr;
	
        /*starting writing seq whic is  
	        S-(saddr+w)-ACK-maddr-ACK */
        I2C2->MCS = 3; 
        error = I2C_wait_till_done(2);        /* wait until write is complete */
        if (error) return error;
	
        /* sending data and waiting for ack and then sending stop */
        I2C2->MDR = data;                     /* loading data  in data reg*/
        I2C2->MCS = 5;                        /* -data-ACK-P */
        /*error = I2C_wait_till_done(2);*/    /*this line not working (checking ack_address)      /* wait until write is complete */
        while(I2C2->MCS & 0x40);              /* wait until bus is not busy */
        error = I2C2->MCS & 0xA;              /*checking that there are no error and ack_data is recived */ 
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;
		
		case 3:
        /* send slave address and starting address to their regestiers  */
        I2C3->MSA = slaveAddr << 1;
        I2C3->MDR = memAddr;
	
        /*starting writing seq whic is  
	        S-(saddr+w)-ACK-maddr-ACK */
        I2C3->MCS = 3; 
        error = I2C_wait_till_done(3);        /* wait until write is complete */
        if (error) return error;
	
        /* sending data and waiting for ack and then sending stop */
        I2C3->MDR = data;                     /* loading data  in data reg*/
        I2C3->MCS = 5;                        /* -data-ACK-P */
        /*error = I2C_wait_till_done(0);*/    /*this line not working (checking ack_address)      /* wait until write is complete */
        while(I2C3->MCS & 0x40);              /* wait until bus is not busy */
        error = I2C3->MCS & 0xA;              /*checking that there are no error and ack_data is recived */ 
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;    
	}
}

/*****************************************************************
***********Describtion : Read one byte only **********************

*******      Required  : 1-i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3- memory addres location of the data you want
                         4- pointer to save the reading data 

***** byte write seq : S-(saddr+w)-ACK-maddr-ACK-
                       R-(saddr+r)-ACK-data-NACK-P
         
** return : 8_bit variable erorr if this a problem ***************
            or zero (0) if evrey thing is okay
******************************************************************/

uint8_t I2C_byteread(int8_t I2C_NUM ,int8_t slaveAddr, int8_t memAddr, uint8_t* data)
{
uint8_t error;
	
	switch(I2C_NUM)
	{
		case 0:
       /* send slave address and starting address */
       I2C0->MSA = slaveAddr << 1;
       I2C0->MDR = memAddr;
       I2C0->MCS = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(0);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C0->MSA = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C0->MCS = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(0);
       if (error) return error;

       *data = I2C0->MDR;                         /* store data received */

       while(I2C0->MCS & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;
		
		case 1:
       /* send slave address and starting address */
       I2C1->MSA = slaveAddr << 1;
       I2C1->MDR = memAddr;
       I2C1->MCS = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(1);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C1->MSA = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C1->MCS = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(1);
       if (error) return error;

       *data = I2C1->MDR;                         /* store data received */

       while(I2C1->MCS & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;
		
		case 2:
       /* send slave address and starting address */
       I2C2->MSA = slaveAddr << 1;
       I2C2->MDR = memAddr;
       I2C2->MCS = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(2);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C2->MSA = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C2->MCS = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(2);
       if (error) return error;

       *data = I2C2->MDR;                         /* store data received */

       while(I2C2->MCS & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;
		
		case 3:
       /* send slave address and starting address */
       I2C3->MSA = slaveAddr << 1;
       I2C3->MDR = memAddr;
       I2C3->MCS = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(3);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C3->MSA = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C3->MCS = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(3);
       if (error) return error;

       *data = I2C3->MDR;                         /* store data received */

       while(I2C3->MCS & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;

	}
}	

/*******************************************************************
***********Describtion : Write n bytes of data ***********************

*******      Required  : 1-i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3-  first memory addres location of the data 
                         4- pointer to the memory location to the data 

***** byte write seq : S-(saddr+w)-ACK-maddr-ACK-data-ACK-P *********
         
** return : 8_bit variable erorr if this a problem ******************
            or zero (0) if evrey thing is okay
*********************************************************************/

uint8_t I2C_burstWrite(int8_t I2C_NUM,int8_t slaveAddr, int8_t memAddr, int8_t byteCount, uint8_t* data)
{
	uint8_t error;
	
if (byteCount <= 0)
return -1;                                /* no write was performed */

switch(I2C_NUM)
{
	case 0:
      /* send slave address and starting address */
      I2C0->MSA = slaveAddr << 1;
      I2C0->MDR = memAddr;
      I2C0->MCS = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(0);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C0->MDR = *data++;                     /* write the next byte */
        I2C0->MCS = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(0);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C0->MDR = *data++;                    /* write the last byte */
      I2C0->MCS = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(0);
      while(I2C0->MCS & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
	    break;
			 
	case 1:
      /* send slave address and starting address */
      I2C1->MSA = slaveAddr << 1;
      I2C1->MDR = memAddr;
      I2C1->MCS = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(1);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C1->MDR = *data++;                     /* write the next byte */
        I2C1->MCS = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(1);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C1->MDR = *data++;                    /* write the last byte */
      I2C1->MCS = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(1);
      while(I2C1->MCS & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
		  break; 
			 
	case 2:
      /* send slave address and starting address */
      I2C2->MSA = slaveAddr << 1;
      I2C2->MDR = memAddr;
      I2C2->MCS = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(2);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C2->MDR = *data++;                     /* write the next byte */
        I2C2->MCS = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(2);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C2->MDR = *data++;                    /* write the last byte */
      I2C2->MCS = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(2);
      while(I2C2->MCS & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
		  break; 		

  case 3:
      /* send slave address and starting address */
      I2C3->MSA = slaveAddr << 1;
      I2C3->MDR = memAddr;
      I2C3->MCS = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(3);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C3->MDR = *data++;                     /* write the next byte */
        I2C3->MCS = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(3);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C3->MDR = *data++;                    /* write the last byte */
      I2C3->MCS = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(3);
      while(I2C3->MCS & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
		  break; 			 
    }
}

/*****************************************************************
***********Describtion : Read n bytes of data**********************

*******      Required  : 1- i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3- first memory addres location of the data you want
                         4- pointer to save the reading data 

***** byte write seq : S-(saddr+w)-ACK-maddr-ACK-
                       R-(saddr+r)-ACK-data-NACK-P
         
** return : 8_bit variable erorr if this a problem ***************
            or zero (0) if evrey thing is okay
******************************************************************/

uint8_t I2C_burstread(int8_t I2C_NUM,int8_t slaveAddr, int8_t memAddr, int8_t byteCount, uint8_t* data)

{
	
	uint8_t error;
	
if (byteCount <= 0)
return -1; /* no read was performed */

switch(I2C_NUM)
{
	
 case 0 :
       /* send slave address and starting address */
       I2C0->MSA = slaveAddr << 1;
       I2C0->MDR = memAddr;
       I2C0->MCS = 3;                               /* S-(saddr+w)-ACK-maddr-ACK */

	     error = I2C_wait_till_done(0);
       if (error) return error;
	
       /* to change bus from write to read, send restart with slave addr */
       I2C0->MSA = (slaveAddr << 1) + 1;              /* restart: -R-(saddr+r)-ACK */
       if (byteCount == 1)                           /* if last byte, don't ack */
       I2C0->MCS = 7;                               /* -data-NACK-P */
       else                                        /* else ack */
       I2C0->MCS = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(0);
       if (error) return error;
			 
       *data++ = I2C0->MDR;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C0->MCS & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }
				
       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C0->MCS = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(0);
         if (error) return error;
         byteCount--;
         *data++ = I2C0->MDR;                /* store data received */
        }
				
       I2C0->MCS = 5;                        /* -data-NACK-P */
       error = I2C_wait_till_done(1);
       *data = I2C0->MDR;                   /* store data received */
       while(I2C0->MCS & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
	     break;
				
 case 1 :
       /* send slave address and starting address */
       I2C1->MSA = slaveAddr << 1;
       I2C1->MDR = memAddr;
       I2C1->MCS = 3;                               /* S-(saddr+w)-ACK-maddr-ACK */

	     error = I2C_wait_till_done(1);
       if (error) return error;
	
       /* to change bus from write to read, send restart with slave addr */
       I2C1->MSA = (slaveAddr << 1) + 1;              /* restart: -R-(saddr+r)-ACK */
       if (byteCount == 1)                           /* if last byte, don't ack */
       I2C1->MCS = 7;                               /* -data-NACK-P */
       else                                        /* else ack */
       I2C1->MCS = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(1);
       if (error) return error;
			 
       *data++ = I2C1->MDR;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C1->MCS & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }
				
       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C1->MCS = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(1);
         if (error) return error;
         byteCount--;
         *data++ = I2C1->MDR;                /* store data received */
        }
				
       I2C1->MCS = 5;                        /* -data-NACK-P */
       error = I2C_wait_till_done(1);
       *data = I2C1->MDR;                   /* store data received */
       while(I2C1->MCS & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
       break;
				
	case 2 :
       /* send slave address and starting address */
       I2C2->MSA = slaveAddr << 1;
       I2C2->MDR = memAddr;
       I2C2->MCS = 3;                               /* S-(saddr+w)-ACK-maddr-ACK */

	     error = I2C_wait_till_done(2);
       if (error) return error;
	
       /* to change bus from write to read, send restart with slave addr */
       I2C2->MSA = (slaveAddr << 1) + 1;              /* restart: -R-(saddr+r)-ACK */
       if (byteCount == 1)                           /* if last byte, don't ack */
       I2C2->MCS = 7;                               /* -data-NACK-P */
       else                                        /* else ack */
       I2C2->MCS = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(2);
       if (error) return error;
			 
       *data++ = I2C2->MDR;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C2->MCS & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }
				
       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C2->MCS = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(2);
         if (error) return error;
         byteCount--;
         *data++ = I2C2->MDR;                /* store data received */
        }
				
       I2C2->MCS = 5;                        /* -data-NACK-P */
       error = I2C_wait_till_done(2);
       *data = I2C2->MDR;                   /* store data received */
       while(I2C2->MCS & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
				break;
				
	case 3 :
       /* send slave address and starting address */
       I2C3->MSA = slaveAddr << 1;
       I2C3->MDR = memAddr;
       I2C3->MCS = 3;                               /* S-(saddr+w)-ACK-maddr-ACK */

	     error = I2C_wait_till_done(3);
       if (error) return error;
	
       /* to change bus from write to read, send restart with slave addr */
       I2C3->MSA = (slaveAddr << 1) + 1;              /* restart: -R-(saddr+r)-ACK */
       if (byteCount == 1)                           /* if last byte, don't ack */
       I2C3->MCS = 7;                               /* -data-NACK-P */
       else                                        /* else ack */
       I2C3->MCS = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(3);
       if (error) return error;
			 
       *data++ = I2C3->MDR;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C3->MCS & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }
				
       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C3->MCS = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(3);
         if (error) return error;
         byteCount--;
         *data++ = I2C3->MDR;                /* store data received */
        }
				
       I2C3->MCS = 5;                        /* -data-NACK-P */
       error = I2C_wait_till_done(3);
       *data = I2C3->MDR;                   /* store data received */
       while(I2C3->MCS & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
				break;
  }
}