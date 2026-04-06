# Some include moudles.
import tkinter as tk
from tkinter import font
from tkinter import filedialog
from tkinter import messagebox
import core

# A single class, just could select one class.
the_class = None

# The button to select class file function.
def select_class_file():
    select_class_path = filedialog.askopenfilename(
        title="选择你的班级txt文件",
        filetypes=[("文本文件", "*.txt")]
    )
    if select_class_path:
        entry_path.delete(0, tk.END)
        entry_path.insert(0, select_class_path)

# The button to initialize class file.
def init_class_file():
    global the_class
    the_class = core.myClass(var_user_path.get())
    if the_class is None or the_class.get_data() == 0:
        the_class = None
        messagebox.showerror("班级载入失败", "程序未能载入您的班级，原因可能有两个：\n1. 你的班级文件不存在。\n2. 没有给名字打上性别标识符（男b，女g）。")
    else:
        messagebox.showinfo("班级载入成功", "班级载入完毕，你可以进行点名了。")

# The button to get information about a class.
def check_class_file():
    global the_class
    if the_class is None  or the_class.get_data() == 0:
        messagebox.showerror("无法进行查询", "班级实例不存在，请先载入班级文件！")
        return
    info = the_class.get_data()
    messagebox.showinfo("班级信息", f"版级一共有 {info[0]} 人。\n有 {info[1]} 名男生， {info[2]} 名女生。")

# The button to select names and write result to the entry.
def select_name():
    global the_class
    global var_user_final_people
    if the_class is None  or the_class.get_data() == 0:
        messagebox.showerror("无法进行点名", "班级实例不存在，请先载入班级文件！")
        return
    info = the_class.get_data()
    if var_user_people.get() > info[0] or var_user_people_female.get() + var_user_people_male.get() > info[0]:
        messagebox.showerror("无法进行点名", "你点的人太多了，请您稍微减少人数！")
        return
    if var_user_people_male.get() > info[1] or var_user_people_female.get() > info[2]:
        messagebox.showerror("无法进行点名", "班级内的男女生没有那么多！")
        return
    if var_user_with_gender.get() == False:
        get_name = the_class.chosen_name_with_no_gender(var_user_people.get())
    else:
        get_name = the_class.chosen_name_with_gender(var_user_people_male.get(), var_user_people_female.get())
    final_result = ''.join(name + ', ' for name in get_name)
    var_user_final_people.set(final_result)
    if var_user_with_gender.get() == False:
        messagebox.showinfo("点名完成", f"此次点名点了 {var_user_people.get()} 人")
    else:
        messagebox.showinfo("点名完成", f"此次点名点了 {var_user_people_male.get()} 男生，{var_user_people_female.get()} 女生")

# The button to get output log.
def get_output():
    global the_class
    if the_class is None  or the_class.get_data() == 0:
        messagebox.showerror("无法进行导出", "班级实例不存在，请先载入班级文件！")
        return
    with open('name_output.txt', 'w', encoding='utf-8') as outputfile:
        the_class.output_data(outputfile)
    messagebox.showinfo("日志导出", "日志导出完毕，请在根目录中寻找name_output.txt")

# The button to change whether choose name with gender or not.
def disable_entry():
    if(entry_people_male['state'] == 'normal'):
        entry_people_male.config(state='disabled')
        entry_people_female.config(state='disabled')
        entry_people.config(state='normal')
    else:
        entry_people_male.config(state='normal')
        entry_people_female.config(state='normal')
        entry_people.config(state='disabled')

# The main window.
selectMain = tk.Tk()
selectMain.title("简单点名器")
screen_weight = selectMain.winfo_screenwidth()
screen_height = selectMain.winfo_screenheight()
x_p = (screen_weight // 2) - 480
y_p = (screen_height // 2) - 360
selectMain.geometry(f"960x720+{x_p}+{y_p}")
selectMain.resizable(False, False)

# Some vars in choosing name.
var_user_path = tk.StringVar()
var_user_people = tk.IntVar(value=1)
var_user_with_gender = tk.BooleanVar(value=True) 
var_user_people_male = tk.IntVar(value=1)
var_user_people_female = tk.IntVar(value=1) 
var_user_final_people = tk.StringVar()

# Wiogets about selecting names.
label_path = tk.Label(selectMain, text="班级文件路径：")
label_path.grid(row=0, column=0, padx=20, pady=30, sticky="e")


entry_path = tk.Entry(selectMain, textvariable=var_user_path, width=50)
entry_path.grid(row=0, column=1, padx=10, pady=30)

btn_choose_file = tk.Button(selectMain, text='载入班级文件', command=init_class_file, width=15)
btn_choose_file.grid(row=0, column=2, padx=20, pady=30)

btn_select_file = tk.Button(selectMain, text='选择班级文件', command=select_class_file, width=15)
btn_select_file.grid(row=1, column=2, padx=20, pady=30)

check_gender = tk.Checkbutton(
    selectMain, 
    text="按性别点名", 
    variable=var_user_with_gender, 
    command=disable_entry
)
check_gender.grid(row=1, column=1, padx=20, pady=10, sticky="w")

label_people = tk.Label(selectMain, text="点名总人数：")
label_people.grid(row=2, column=0, padx=20, pady=10, sticky="e")
entry_people = tk.Entry(selectMain, textvariable=var_user_people, width=20)
entry_people.grid(row=2, column=1, padx=10, pady=10, sticky="w")

label_male = tk.Label(selectMain, text="男生人数：")
label_male.grid(row=3, column=0, padx=20, pady=10, sticky="e")
entry_people_male = tk.Entry(selectMain, textvariable=var_user_people_male, width=20, state="disabled")
entry_people_male.grid(row=3, column=1, padx=10, pady=10, sticky="w")

label_female = tk.Label(selectMain, text="女生人数：")
label_female.grid(row=4, column=0, padx=20, pady=10, sticky="e")
entry_people_female = tk.Entry(selectMain, textvariable=var_user_people_female, width=20, state="disabled")
entry_people_female.grid(row=4, column=1, padx=10, pady=10, sticky="w")

btn_check_file = tk.Button(selectMain, text='查看班级情况', command=check_class_file, width=15)
btn_check_file.grid(row=5, column=0, padx=20, pady=20)
btn_select_name = tk.Button(selectMain, text='开始点名', command=select_name, width=15, bg="#4CAF50", fg="white")
btn_select_name.grid(row=5, column=1, padx=10, pady=20)
btn_get_output = tk.Button(selectMain, text='导出点名日志', command=get_output, width=15)
btn_get_output.grid(row=5, column=2, padx=20, pady=20)

label_result = tk.Label(selectMain, text="点名结果：")
label_result.grid(row=6, column=0, padx=20, pady=30, sticky="e")
entry_final = tk.Entry(selectMain, textvariable=var_user_final_people, width=60, font=("微软雅黑", 14))
entry_final.grid(row=6, column=1, columnspan=2, padx=10, pady=30) 

disable_entry()

selectMain.mainloop()