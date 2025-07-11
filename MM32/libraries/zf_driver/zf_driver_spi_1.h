/*********************************************************************************************************************
* MM32F327X-G8P Opensourec Library 即（MM32F327X-G8P 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 MM32F327X-G8P 开源库的一部分
* 
* MM32F327X-G8P 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_spi
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.37
* 适用平台          MM32F327X_G8P
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/

#ifndef _zf_driver_spi_h_
#define _zf_driver_spi_h_

#include "zf_common_typedef.h"

#define SPI_SPEED_PRIORITY                                                      // SPI 通信速度优先

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // SPI1 引脚 SCK
    SPI1_SCK_A5         = 0x0505,                                               // 0x 0[SPI1] 5[AF5] 05[A5]
    SPI1_SCK_B3         = 0x0523,                                               // 0x 0[SPI1] 5[AF5] 23[B3]
    SPI1_SCK_E12        = 0x058C,                                               // 0x 0[SPI1] 5[AF5] 8C[E12]

    // SPI2 引脚 SCK
    SPI2_SCK_B10        = 0x152A,                                               // 0x 1[SPI2] 5[AF5] 2A[B10]
    SPI2_SCK_B13        = 0x152D,                                               // 0x 1[SPI2] 5[AF5] 2D[B13]
    SPI2_SCK_D3         = 0x1563,                                               // 0x 1[SPI2] 5[AF5] 63[D3]
    SPI2_SCK_E2         = 0x1582,                                               // 0x 1[SPI2] 5[AF5] 82[E2]
}spi_sck_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // SPI1 引脚 MOSI
    SPI1_MOSI_A7        = 0x0507,                                               // 0x 0[SPI1] 5[AF5] 07[A7]
    SPI1_MOSI_B5        = 0x0525,                                               // 0x 0[SPI1] 5[AF5] 25[B5]
    SPI1_MOSI_E14       = 0x058E,                                               // 0x 0[SPI1] 5[AF5] 8E[E14]

    // SPI2 引脚 MOSI
    SPI2_MOSI_B15       = 0x152F,                                               // 0x 1[SPI2] 5[AF5] 2F[B15]
    SPI2_MOSI_C3        = 0x1543,                                               // 0x 1[SPI2] 5[AF5] 43[C3]
    SPI2_MOSI_E6        = 0x1586,                                               // 0x 1[SPI2] 5[AF5] 86[E6]
}spi_mosi_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    SPI_MISO_NULL       = 0xFFFF,                                               // 不使用硬件 MISO 引脚就填这个

    // SPI1 引脚 MISO
    SPI1_MISO_A6        = 0x0506,                                               // 0x 0[SPI1] 5[AF5] 06[A6]
    SPI1_MISO_B4        = 0x0524,                                               // 0x 0[SPI1] 5[AF5] 24[B4]
    SPI1_MISO_E13       = 0x058D,                                               // 0x 0[SPI1] 5[AF5] 8D[E13]

    // SPI2 引脚 MISO
    SPI2_MISO_B14       = 0x152E,                                               // 0x 1[SPI2] 5[AF5] 2E[B14]
    SPI2_MISO_C2        = 0x1542,                                               // 0x 1[SPI2] 5[AF5] 42[C2]
    SPI2_MISO_C6        = 0x1546,                                               // 0x 1[SPI2] 5[AF5] 46[C6]
    SPI2_MISO_E5        = 0x1585,                                               // 0x 1[SPI2] 5[AF5] 85[E5]
}spi_miso_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    SPI_CS_NULL         = 0xFFFF,                                               // 不使用硬件 CS 引脚就填这个

    // SPI1 引脚 CS
    SPI1_CS_A4          = 0x0504,                                               // 0x 0[SPI1] 5[AF5] 04[A4]
    SPI1_CS_A15         = 0x050F,                                               // 0x 0[SPI1] 5[AF5] 0F[A15]
    SPI1_CS_E11         = 0x058B,                                               // 0x 0[SPI1] 5[AF5] 8B[E11]

    // SPI2 引脚 CS
    SPI2_CS_B9          = 0x1529,                                               // 0x 1[SPI2] 5[AF5] 29[B9]
    SPI2_CS_B12         = 0x152C,                                               // 0x 1[SPI2] 5[AF5] 2C[B12]
    SPI2_CS_E3          = 0x1583,                                               // 0x 1[SPI2] 5[AF5] 83[E3]
    SPI2_CS_E4          = 0x1584,                                               // 0x 1[SPI2] 5[AF5] 84[E4]
}spi_cs_pin_enum;

typedef enum                                                                    // 枚举 SPI 模式 此枚举定义不允许用户修改
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}spi_mode_enum;

typedef enum                                                                    // 枚举 SPI 编号 此枚举定义不允许用户修改
{
    SPI_1,
    SPI_2,
}spi_index_enum;

void        spi_write_8bit                  (spi_index_enum spi_n, const uint8 data);
void        spi_write_8bit_array            (spi_index_enum spi_n, const uint8 *data, uint32 len);

void        spi_write_16bit                 (spi_index_enum spi_n, const uint16 data);
void        spi_write_16bit_array           (spi_index_enum spi_n, const uint16 *data, uint32 len);

void        spi_write_8bit_register         (spi_index_enum spi_n, const uint8 register_name, const uint8 data);
void        spi_write_8bit_registers        (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 len);

void        spi_write_16bit_register        (spi_index_enum spi_n, const uint16 register_name, const uint16 data);
void        spi_write_16bit_registers       (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 len);

uint8       spi_read_8bit                   (spi_index_enum spi_n);
void        spi_read_8bit_array             (spi_index_enum spi_n, uint8 *data, uint32 len);

uint16      spi_read_16bit                  (spi_index_enum spi_n);
void        spi_read_16bit_array            (spi_index_enum spi_n, uint16 *data, uint32 len);

uint8       spi_read_8bit_register          (spi_index_enum spi_n, const uint8 register_name);
void        spi_read_8bit_registers         (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 len);

uint16      spi_read_16bit_register         (spi_index_enum spi_n, const uint16 register_name);
void        spi_read_16bit_registers        (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 len);

void        spi_transfer_8bit               (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len);
void        spi_transfer_16bit              (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len);

void        spi_init                        (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define spi_mosi(spi_n, mosi, miso, len)    (spi_transfer_8bit((spi_n), (mosi), (miso), (len)))
#endif

#endif
