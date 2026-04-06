import os
import random

# The inner implementation about the select_name.

class myClass:
  # Check The classfile is existed or not.
  @staticmethod
  def check(filepath):
    if os.path.isfile(filepath):
      return open(filepath, 'r', encoding='utf-8')
    else:
      return None
  # Check the classfile is legal.
  @staticmethod
  def count(name_list):
    male_list, female_list = [], []
    for name in name_list:
      if 'b' in name:
        male_list.append(name[:-1])
      elif 'g' in name:
        female_list.append(name[:-1])
      else:
        return [[], []]
    return [male_list, female_list]
  
  # Override the __new__ about creating a class.
  def __new__(cls, class_file):
    the_class_file =  cls.check(class_file)
    if the_class_file is None:
      return None
    the_class = super().__new__(cls)
    return the_class
  
  # Initialzation a class.
  def __init__(self, a_class):
    with open(a_class, 'r', encoding='utf-8') as f:
      self.name_list = [line.rstrip('\n') for line in f]
    self.name_number = len(self.name_list)
    self.get_name = self.count(self.name_list)
    self.male, self.female = self.get_name[0], self.get_name[1]
    self.count_name = {a_name[:-1] : 0 for a_name in self.name_list}
    self.male_number, self.female_number = len(self.male), len(self.female)
    
  # Return information about a class.
  def get_data(self):
    if self.female_number == 0 and self.male_number == 0:
      return 0
    info = [self.name_number, self.male_number, self.female_number]
    return info
  
  # Choosing names with gender. Input two integral numbers.
  def chosen_name_with_gender(self, males, females):
    self.chosen_name_in_male = random.sample(range(0, self.male_number), males)
    self.chosen_name_in_female = random.sample(range(0, self.female_number), females)
    chosen_name = []
    for index in self.chosen_name_in_male:
      chosen_name.append(self.male[index])
      self.count_name[self.male[index]] += 1
    for index in self.chosen_name_in_female:
      chosen_name.append(self.female[index])
      self.count_name[self.female[index]] += 1
    random.shuffle(chosen_name)
    return chosen_name
  
  # Chossing names with no gender. Input a integral numbers.
  def chosen_name_with_no_gender(self, people):
    chosen_index = random.sample(range(0, self.name_number), people)
    chosen_name = []
    for index in chosen_index:
      chosen_name.append(self.name_list[index][:-1])
      self.count_name[self.name_list[index][:-1]] += 1
    return chosen_name
  
  # Output the logs. To check the result.
  def output_data(self, output_file):
    output_list = [names + ' 被点到了 ' + str(cnt) + ' 次\n' for names, cnt in self.count_name.items()]
    output_file.writelines(output_list)  

# Since it is the inner implementation, so it main function do nothing.
if __name__ == "__main__":
  pass