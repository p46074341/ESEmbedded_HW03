HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [8=D] **If you volunteer to give the presentation next week, check this.**

--------------------

**★★★ Please take your note here ★★★**

我修改了main.c的code，加入兩個function,其中function1c0函式傳遞四個int型態的值(a, b, c, d)並回傳(a+b+c-d)，而caller1函式則是無傳遞值但回傳function1(4, 3, 2, 1)，如下圖

![image1](https://github.com/p46074341/ESEmbedded_HW03/blob/master/picture/1.png)
	
接下來利用qemu觀察函數傳遞與回傳的過程

#function1
1. 利用movs指令在r0、r1、r2、r3分別填入四個傳遞值1、2、3、4
2. 利用str指令將r0的值寫入r7 offset #12的位置,r1寫入r7 offset #8的位置,r0寫入r7 offset #4的位置,r3寫入r7 (如圖步驟0x22~0x28)
![image2](https://github.com/p46074341/ESEmbedded_HW03/blob/master/picture/2.png)
3. 步驟二的值依序為傳遞值的a、b、c、d，函式需要回傳a+b+c-d的值，先計算a+b的部分，將a和b利用ldr指令從位置r7 offset #12、r7 offset #8載入r2、r3，接著用add指令將r3加到r2完成a+b的計算重複以上步驟其中減的部分將指令從add換成subs
![image3](https://github.com/p46074341/ESEmbedded_HW03/blob/master/picture/2.png)

#caller1
1. 因為caller1函式回傳值為function1(4, 3, 2, 1),因此一樣用movs指令分別在r0、r1、r2、r3填入4、3、2、1,接著會透過bx指令跳到0x20重複之前function1的步驟的2、3部分完成計算
![image4](https://github.com/p46074341/ESEmbedded_HW03/blob/master/picture/4.png)
