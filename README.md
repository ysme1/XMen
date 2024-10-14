## 项目名称
EasyXMen是面向嵌入式电子控制单元场景的实时安全操作系统，具有安全性、可靠性、实时性和可移植性等特点。

## 项目特点
具有广泛的可扩展性，完善的系统服务和调度机制，可快速适应在多种硬件平台上部署运行
支持CAN/CANFD、LIN、Ethernet多种总线通信，适用不同通信需求和场景
提供功能安全机制检测和阻止软件故障，实现系统的功能安全保护
采用架构模块化设计思路，便于软件的升级和维护

## 代码地址
https://atomgit.com/easyxmen/XMen

## 目录结构
```
├── BSWCode                 # 模块静态代码
│   ├── CommonInclude       # 共用的头文件
│   ├── Communication       # 通信模块代码
│   ├── Crypto              # 加密模块代码
│   ├── Libraries           # Lib库代码
│   ├── Memory              # 存储模块代码
│   └── SystemServices      # 系统服务模块代码
├── Drivers                 # 板级外设芯片代码
├── Examples                # 示例工程
├── RTE                     # RTE代码
│   └── StaticCode          # RTE 静态代码
├── RTOS                    # OS 代码
│   ├── Extend              # OS 扩展代码
│   ├── Kernel              # OS 内核代码
│   └── Portable            # OS移植代码
│       ├── Mcu             # MCU相关的移植代码
│       └── Processor       # 处理器架构相关移植代码
└── Test                    # bsw模块测试代码
    └── UT                  # 单元测试代码
```
补充说明

- Portable/Mcu 下一个芯片一个目录，比如TC397,S32K148

- Portable/Processor 一种芯片架构一个目录，比如arm,RISC-V

- Test/UT 下一个Bsw模块一个目录

- Drivers 下放置板级外设芯片实现代码，例如 TJA1101

- Examples 下以一个硬件板型+具体功能组合成目录名，例如S32K148EVB_Q147_Demo

  - 工程对仓库中已有的实现代码进行引用

  - 工程应实现自动化编译

  - 工程的内部目录供参考

   ```log
    ├── MCAL                    # MCAL 静态代码
    ├── Asw                     # 应用代码
    |   ├── src                 # 应用源码
    |   └── gen                 # 应用配置生成
    ├── PaltformFils            # 编译器等平台相关
    └── ConfigProj              # 配置工程
        ├── BswCfgProj          # bsw 配置工程
        ├── SwcCfgProj          # swc 配置工程
        └── McalCfgProj         # MCAL 配置工程
   ```

    

# 运行条件

协议栈静态代码需要结合开发工具进行使用，开发工具获取地址为：待补充
使用工具需要获取Licence，获取地址链接为：待补充
各模块配置、工具使用方法，可参考对应用户手册
提供基于特定芯片平台Demo工程，可通过配置工具获取使用

## 项目状态
EasyXMen目前支持NXP S32K148平台

## 开源许可
EasyXMen项目遵循许可证LGPL V2.1版本

## 协作者
> 高效的协作会激发无尽的创造力，将他们的名字记录在这里吧
普华基础软股份有限公司

