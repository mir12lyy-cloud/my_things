# -*- coding = utf-8 -*-
import random
class Myclass:
    def check(filename):
        try:
            classfile = open(filename, 'r', encoding='utf-8')
            return classfile
        except IOError:
            print("看上去你没有构建name.txt\n记得去创建一个\n并且保证男女名字后面有一个标识符（男b，女g）")
            input("按任意键退出")
            exit()
    def count(self):
        male_list, females_list = [], []
        for name in self.name_list:
            if 'b' in name:
                male_list.append(name[:-1])
            elif 'g' in name:
                females_list.append(name[:-1])
            else:
                print("文件格式错误，记得加上性别标识符（男b，女g）")
                exit()
        return [male_list, females_list]    
    def __init__(self, classfile):
        a_class = Myclass.check(classfile)
        self.name_list = a_class.readlines()
        self.name_number = len(self.name_list)
        self.sex = Myclass.count(self)
        self.male = self.sex[0]
        self.male_number = len(self.male)
        self.female = self.sex[1]
        self.female_number = len(self.female) 
    def chosen_name_with_sex(self, males, females):
        chosen_index_in_male = random.sample(range(0, self.male_number + 1), males)
        chosen_index_in_female = random.sample(range(0, self.female_number + 1), females)
        self.chosenname = []
        for index in chosen_index_in_male:
            self.chosenname.append(self.male[index])
        for index in chosen_index_in_female:
            self.chosenname.append(self.female[index])
        random.shuffle(self.chosenname)
        for name in self.chosenname:
            print(name)
    def chosen_name_no_sex(self, people):
        chosen_index = random.sample(range(0, self.name_number + 1), people)
        self.chosenname = []
        for index in chosen_index:
            self.chosenname.append(self.name_list[index][:-1])
        for name in self.chosenname:
            print(name)
