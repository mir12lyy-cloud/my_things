import tkinter as tk
from tkinter import font

selectMain = tk.Tk()
selectMain.title("简单点名器")
selectMain.geometry("720x540")

def load_class_file():
    pass

def check_class_file():
    pass

def select_name():
    pass

def get_output():
    pass

tk.Label(selectMain, text='点名器（可点性别，带日志）', font=('TkDefaultFont', 22)).place(x=175, y=50)

tk.Label(selectMain, text='输入班级文件位置：').place(x=50, y=120)
tk.Label(selectMain, text='输入你要点的人数：').place(x=50, y=160)
tk.Label(selectMain, text='输入点的男生人数（不指定性别不用填）：').place(x=50, y=200)
tk.Label(selectMain, text='输入点的女生人数（不指定性别不用填）：').place(x=50, y=240)

var_user_path = tk.StringVar()
var_user_people = tk.IntVar()
var_user_people_male = tk.IntVar()
var_user_people_female = tk.IntVar()

var_user_selectwithsex = tk.BooleanVar()

entry_path = tk.Entry(selectMain, textvariable=var_user_path)
entry_path.place(x=360, y=120)
entry_people = tk.Entry(selectMain, textvariable=var_user_people)
entry_people.place(x=360, y=160)
entry_people_male = tk.Entry(selectMain, textvariable=var_user_people_male)
entry_people_male.place(x=360, y=200)
entry_people_female = tk.Entry(selectMain, textvariable=var_user_people_female)
entry_people_female.place(x=360, y=240)

def disable_entry():
    if(entry_people_male['state'] == 'normal'):
        entry_people_male.config(state='disabled')
        entry_people_female.config(state='disabled')
    else:
        entry_people_male.config(state='normal')
        entry_people_female.config(state='normal')

cbtn_comfirm_sex = tk.Checkbutton(selectMain, text='指定性别', variable=var_user_selectwithsex, onvalue=True, offvalue=False, command=disable_entry)
cbtn_comfirm_sex.place(x=50, y=300)

btn_load_file = tk.Button(selectMain, text='载入班级文件', command=load_class_file)
btn_load_file.place(x=60, y=400)
btn_check_file = tk.Button(selectMain, text='查看班级情况', command=check_class_file)
btn_check_file.place(x=200, y=400)
btn_select_name = tk.Button(selectMain, text='点名', command=select_name)
btn_select_name.place(x=340, y=400)
btn_get_output = tk.Button(selectMain, text='输出日志', command=get_output)
btn_get_output.place(x=480, y=400)

selectMain.mainloop()