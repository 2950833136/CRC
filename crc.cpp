#include <stdio.h>
#include "type.h"
#include "CRC.h"

/*****************************************************************************
*function name:reverse8
*function: �ֽڷ�ת����1100 0101 ��ת��Ϊ1010 0011
*input��1�ֽ�
*output:��ת���ֽ�
******************************************************************************/
u8 reverse8(u8 data)
{
    u8 i;
    u8 temp = 0;
    for (i = 0; i < 8; i++)	    //�ֽڷ�ת
        temp |= ((data >> i) & 0x01) << (7 - i);
    return temp;
}
/*****************************************************************************
*function name:reverse16
*function: ˫�ֽڷ�ת����1100 0101 1110 0101��ת��Ϊ1010 0111 1010 0011
*input��˫�ֽ�
*output:��ת��˫�ֽ�
******************************************************************************/
u16 reverse16(u16 data)
{
    u8 i;
    u16 temp = 0;
    for (i = 0; i < 16; i++)	//��ת
        temp |= ((data >> i) & 0x0001) << (15 - i);
    return temp;
}
/*****************************************************************************
*function name:reverse32
*function: 32bit�ַ�ת
*input��32bit��
*output:��ת��32bit��
******************************************************************************/
u32 reverse32(u32 data)
{
    u8 i;
    u32 temp = 0;
    for (i = 0; i < 32; i++)	//��ת
        temp |= ((data >> i) & 0x01) << (31 - i);
    return temp;
}

/*****************************************************************************
*function name:crc8
*function: CRCУ�飬У��ֵΪ8λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���type-CRC8���㷨����
*output:8λУ��ֵ
******************************************************************************/
u8 crc8(u8* addr, int num, CRC_8 type)
{
    u8 data;
    u8 crc = type.InitValue;                    //��ʼֵ
    int i;
    for (; num > 0; num--)
    {
        data = *addr++;
        if (type.InputReverse == TRUE)
            data = reverse8(data);              //�ֽڷ�ת
        crc = crc ^ data;                       //��crc��ʼֵ��� 
        for (i = 0; i < 8; i++)                 //ѭ��8λ 
        {
            if (crc & 0x80)                     //�����Ƴ���λΪ1�����ƺ������ʽ���
                crc = (crc << 1) ^ type.Poly;
            else                                //����ֱ������
                crc <<= 1;
        }
    }
    if (type.OutputReverse == TRUE)             //������������ת
        crc = reverse8(crc);
    crc = crc ^ type.XorOut;                    //����������ֵ���
    return(crc);                                //��������У��ֵ
}

/*****************************************************************************
*function name:crc16
*function: CRCУ�飬У��ֵΪ16λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���type-CRC16���㷨����
*output:16λУ��ֵ
******************************************************************************/
u16 crc16(u8* addr, int num, CRC_16 type)
{
    u8 data;
    u16 crc = type.InitValue;					//��ʼֵ
    int i;
    for (; num > 0; num--)
    {
        data = *addr++;
        if (type.InputReverse == TRUE)
            data = reverse8(data);				//�ֽڷ�ת
        crc = crc ^ (data << 8);				//��crc��ʼֵ��8λ��� 
        for (i = 0; i < 8; i++)					//ѭ��8λ 
        {
            if (crc & 0x8000)					//�����Ƴ���λΪ1�����ƺ������ʽ���
                crc = (crc << 1) ^ type.Poly;
            else		                        //����ֱ������
                crc <<= 1;
        }
    }
    if (type.OutputReverse == TRUE)             //������������ת
        crc = reverse16(crc);
    crc = crc ^ type.XorOut;	                //����������ֵ���
    return(crc);                                //��������У��ֵ
}
/*****************************************************************************
*function name:crc32
*function: CRCУ�飬У��ֵΪ32λ
*input:addr-�����׵�ַ��num-���ݳ��ȣ��ֽڣ���type-CRC32���㷨����
*output:32λУ��ֵ
******************************************************************************/
u32 crc32(u8* addr, int num, CRC_32 type)
{
    u8 data;
    u32 crc = type.InitValue;					//��ʼֵ
    int i;
    for (; num > 0; num--)
    {
        data = *addr++;
        if (type.InputReverse == TRUE)
            data = reverse8(data);				//�ֽڷ�ת
        crc = crc ^ (data << 24);				//��crc��ʼֵ��8λ��� 
        for (i = 0; i < 8; i++)					//ѭ��8λ 
        {
            if (crc & 0x80000000)				//�����Ƴ���λΪ1�����ƺ������ʽ���
                crc = (crc << 1) ^ type.Poly;
            else                                //����ֱ������
                crc <<= 1;
        }
    }
    if (type.OutputReverse == TRUE)             //������������ת
        crc = reverse32(crc);
    crc = crc ^ type.XorOut;	                //����������ֵ���
    return(crc);                                //��������У��ֵ
}
