import os

def WriteSections(A, B, src, S):

    c_file = A # Указатель текущего файла ставим на A
    f = open(src, "r") # Считываем источник данных который является файлом, переданным в функцию
    tmp_arr = [] #Временный массив в который будем читать днные, полагаем, что его длина не превосходит S.
    cur_val = '' # Вспомогательная переменная хранящая в себе текущее считанное значение, создана для удобства
    while True:
        data = f.read(1) #Читаем символ из файла
        if (data != ' '): #Продолжаем создавать строку из числа, которое лежит в файле 
                cur_val += data
        elif(not data): #В случае если файл закончился, у нас могли остаться данные, которые мы не обработали. Записываем их.
            if cur_val:
                tmp_arr.append(int(cur_val))
            tmp_arr.sort() #Для удобства используется встроенная сортировка(дальше аналогично)
            tmp_arr = list(map(str, tmp_arr))
            with open(c_file, "a+") as file:
                file.write(" ".join(tmp_arr))
            break #Т.к файл закончился, стоит выйти из цикла.
        else: #В том случае, если был найден разделитель, необходимо текущее число записать,и начать чтение нового
            if (S != len(tmp_arr)): # Если массив с данными не заполнен до длинны отрезка, сбрасываем cur_val и идём дальше
                    tmp_arr.append(int(cur_val))
                    cur_val = ''
            else: #Если массив заполнен полностью, то записываем отрезок, и меняем файл на запись
                    tmp_arr.sort()
                    tmp_arr = list(map(str, tmp_arr))
                    with open(c_file, "a+") as file:
                        file.write(" ".join(tmp_arr))
                    c_file = B if(c_file == A) else A    
                    tmp_arr = []
                    tmp_arr.append(int(cur_val))
                    cur_val = ''
    f.close() 

def FinalMerge(A, B, C, D, S):
    f_inp = A
    s_inp = B
    cur_out = C
    outputs = [A,B,C,D] #Массив файлов для записи, позже используется для определения текущего файла.

    with open(cur_out, 'wb'): #Очистка cur_out
        pass
    #Условие в цикле означает следующее: Если один из файлов с отрезками пуст, значит в другом находится отсортированный отрезок.
    while((os.stat(f_inp)).st_size != 0 and (os.stat(s_inp)).st_size != 0):             
        f_1 = open(f_inp, "r")   # Читаем оба файла                                            
        f_2 = open(s_inp, "r")
        data_1 = f_1.read(S)
        data_2 = f_2.read(S)
        r_flag = 1
        while(data_1 or data_2): #Пока хотя бы в одном есть данные
            if r_flag == 0:
                data_1 = f_1.read(S)
                data_2 = f_2.read(S)
            # "Сливаем" отрезки
            data_1 = data_1.split()
            data_1 = list(map(int, data_1))
            data_2 = data_2.split()
            data_2 = list(map(int, data_2))

            tmp_data = data_1 + data_2
            tmp_data.sort()
            data = tmp_data
            data = list(map(str, data))
            r_flag = 0
            #Результат слияния записываем в файл и затем обновляем текущий файл записи
            with open(cur_out, "a+") as file:
                file.write(" ".join(data) + " ")
            tmp_index = outputs.index(cur_out)
            cur_out = outputs[(tmp_index + 1) -  (tmp_index % 2) * 2] # Если индекс четный, то указатель вправо, иначе влево.
        f_1.close()
        f_2.close()
        with open(f_inp, 'wb'): 
            pass
        with open(s_inp, 'wb'):
            pass
        
        S *= 2 # Увеличиваем размер отрезка для записи
        if (f_inp == A):
            f_inp = C
            s_inp = D
            cur_out = A
        else:
            f_inp = A
            s_inp = B
            cur_out = C
    
    
A = 'A.txt'  
B = 'B.txt'
C = 'C.txt'
D = 'D.txt'
S = 10 #Размер отрезка, по которому будет идти сортировка
WriteSections(A, B, C, S)
FinalMerge(A, B, C, D, S)