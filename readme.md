此文件夹为PULPino未拓展RISCV，借用https://gitlab.lrz.de/tueisec/post-quantum-crypto代码修改；


### PULPino Platform
下载PULPino平台代码

```bash
git clone https://github.com/pulp-platform/pulpino
./update-ips.py
```
本文件中已经有完整版，可以跳过这一步；



### Install  PULP Toolchain
PULP工具链下载及安装

```bash
git clone --recursive https://github.com/pulp-platform/pulp-riscv-gnu-toolchain
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev
./configure --prefix=/opt/risqv --with-arch=rv32imfcxpulpv3 --with-abi=ilp32 --with-cmodel=medlow
make
```


### Compile a New Source Code and Create Stimuli
打开目录并验证是否可以编译，需要确认工具链安装路径和makefile中指向的路径一致；

```bash
cd COMPILE/compile
make
```

完成验证后可以自己写C语言代码，请根据makefile指令所指向的路径添加文件夹及修改makefile；


### Run Modelsim Simulation

```bash
cd MODELSIM/work
module load mentor/modelsim/latest (if applicable)
vsim
```

在modelsim指令行中输入：do ../scripts/run_pre_syn.do
