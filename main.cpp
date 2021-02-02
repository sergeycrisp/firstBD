
#include <iostream>
#include <locale>

using namespace std;


struct teachers //учителя
{
    int course_number = 1;
    int id_course_dealership;
    char name[20];
    char address[20];
    bool availability = 1;
    int first_entry_address = -1;
};

struct selling //продажи
{
    int course_number = 1;
    int id_course_dealership;
    int id_course;
    int cost;
    bool availability = 1;
    int next_entry_student = -1;
};

struct index_table
{
    int id_course_dealership;
    int course_number = 1;
    bool availability = 1;
};

void ut_m() // выводит все данные с файла S.fl и S.ind
{
    cout << "ФАЙЛ S.fl" << endl << endl;
    FILE* file1;
    if (fopen_s(&file1, "S.fl", "rb"))
        perror("Error");
    else
    {
        teachers str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(teachers), 1, file1);
            if (feof(file1))
                break;
            //cout << "str1.availability: " << str1.availability << endl;
            if (str1.availability)
            {
                //cout << "str1.availability: " << str1.availability << endl;
                cout << "Course number: " << str1.course_number << endl;
                cout << "course author number: " << str1.id_course_dealership << endl;
                cout << "Teachers name: " << str1.name << endl;
                cout << "Teachers adress: " << str1.address << endl;
                cout << "Adress first line in SP.fl: ";
                if (str1.first_entry_address == -1)
                    cout << "No lines";
                else
                    cout << str1.first_entry_address;
                cout << endl << endl;
            }
        }
    }
    fclose(file1);

    cout << endl << endl << "File S.ind" << endl << endl;

    FILE* file2;
    if (fopen_s(&file2, "S.ind", "rb"))
        perror("Error");
    else
    {
        index_table str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(index_table), 1, file2);
            if (feof(file1))
                break;
            if (str1.availability)
            {
                cout << "Number line is в S.fl: " << str1.course_number << endl;
                cout << "id teacher: " << str1.id_course_dealership << endl;
            }
        }
        fclose(file2);
    }

    cout << endl << endl << endl;
}

void ut_s() // выводит все данные с файла SP.fl
{
    cout << "File SP.fl" << endl << endl;
    FILE* file1;
    if (fopen_s(&file1, "Sp.fl", "rb"))
        perror("Error");
    else
    {
        selling str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(selling), 1, file1);
            if (feof(file1))
                break;
            if (str1.availability)
            {
                cout << "id selling: " << str1.course_number << endl;
                cout << "id teacher: " << str1.id_course_dealership << endl;
                cout << "id course: " << str1.id_course << endl;
                cout << "price: " << str1.cost << endl;
                cout << "New line address SP.fl: ";
                if (str1.next_entry_student == -1)
                    cout << "Last line";
                else
                    cout << str1.next_entry_student;
                cout << endl << endl;
            }
        }
        fclose(file1);
    }
    cout << endl << endl << endl;
}

void update_file_S(teachers& showroom) //обновляем файл S
{
    FILE* file1;
    FILE* file2;

    if (fopen_s(&file1, "S.fl", "rb+"))
        perror("Error");
    else
    {
        fseek(file1, sizeof(teachers) * (showroom.course_number - 1), SEEK_SET);
        fwrite(&showroom, sizeof(teachers), 1, file1);
    }
    fclose(file1);
}


void insert_s() //selling_registration (SP.fl)
{
    FILE* file123;
    if (fopen_s(&file123, "SP.fl", "a+b"))
        perror("Error");
    else
        fclose(file123);

    selling registration;
    cout << "Input teachers id: ";
    cin >> registration.id_course_dealership;
    cout << "Input course id: ";
    cin >> registration.id_course;
    cout << "Input price: ";
    cin >> registration.cost;

    FILE* file1;
    if (fopen_s(&file1, "SP.fl", "rb"))
        perror("Error");
    else
    {
        selling str1;
        str1.course_number = 0;
        while (!feof(file1))
        {
            fread(&str1, sizeof(selling), 1, file1);
            if (feof(file1))
                break;
        }
        registration.course_number = str1.course_number + 1;
        cout << "Course number: " << registration.course_number << endl;
        fclose(file1);
    }

    cout << endl << endl;

    FILE* file2;
    teachers str1;

    if (fopen_s(&file2, "S.fl", "rb"))
        perror("Error");
    else
    {
        str1.course_number = 0;
        while (!feof(file2))
        {
            fread(&str1, sizeof(teachers), 1, file2);
            if (feof(file2))
                break;
            if (registration.id_course_dealership == str1.id_course_dealership)
            {
                registration.next_entry_student = str1.first_entry_address;
                str1.first_entry_address = registration.course_number;
                break;
            }
        }
        fclose(file2);
    }


    update_file_S(str1); //обновляем файл S

    FILE* file3;
    if (fopen_s(&file3, "SP.fl", "a+b"))
        perror("Error");
    else
        fwrite(&registration, sizeof(selling), 1, file3);
    fclose(file3);
}

void insert_m() //car_showroom_registration (S.fl)
{
    FILE* file123;
    if (fopen_s(&file123, "S.fl", "a+b"))
        perror("Error");
    else
        fclose(file123);

    teachers registration;
    cout << "Input id teacher: ";
    cin >> registration.id_course_dealership;
    cout << "Input teachers nam: ";
    cin >> registration.name;
    cout << "Input teachers address: ";
    cin >> registration.address;


    FILE* file1;
    if (fopen_s(&file1, "S.fl", "rb"))
        perror("Error");
    else
    {
        teachers str1;
        str1.course_number = 0;
        while (!feof(file1))
        {
            fread(&str1, sizeof(teachers), 1, file1);
            if (feof(file1))
                break;
        }
        registration.course_number = str1.course_number + 1;
        cout << "course_number: " << registration.course_number << endl << endl << endl;
        fclose(file1);
    }

    FILE* file2;
    if (fopen_s(&file2, "S.fl", "a+b"))
        perror("Error");
    else
        fwrite(&registration, sizeof(teachers), 1, file2);
    fclose(file2);



    index_table registration_array;
    registration_array.id_course_dealership = registration.id_course_dealership;
    registration_array.course_number = registration.course_number;
    FILE* file3;

    if (fopen_s(&file3, "S.ind", "a+b"))
        perror("Error");
    else
        fwrite(&registration_array, sizeof(index_table), 1, file3);

    fclose(file3);
}

teachers read(int course_number)
{

    FILE* file1;
    teachers str1;

    if (fopen_s(&file1, "S.fl", "rb"))
        perror("Error");
    else
    {
        fseek(file1, sizeof(teachers) * (course_number - 1), SEEK_SET);
        fread(&str1, sizeof(teachers), 1, file1);
    }
    fclose(file1);

    return str1;
}

teachers get_m() //processing with file S
{

    index_table element;
    teachers salon;

    cout << "Paste in teacher id: ";
    cout << endl;
    cin >> element.id_course_dealership;

    FILE* file1;
    if (fopen_s(&file1, "S.ind", "rb"))
        perror("Error");
    else
    {
        index_table str1;

        while (!feof(file1))
        {
            fread(&str1, sizeof(index_table), 1, file1);
            if (str1.availability && element.id_course_dealership == str1.id_course_dealership)
            {
                salon = read(str1.course_number);
                //делаем что-то с salon
                if (str1.availability)
                {
                    cout << "Course number: " << salon.course_number << endl;
                    cout << "id teacher: " << salon.id_course_dealership << endl;
                    cout << "Name teacher: " << salon.name << endl;
                    cout << "Address teacher: " << salon.address << endl;
                    cout << "Address first line SP.fl: ";
                    if (salon.first_entry_address == -1)
                        cout << "No lines";
                    else
                        cout << salon.first_entry_address;
                    cout << endl << endl;
                }
                else
                    cout << "This car was deleted";
                break;
            }

            if (feof(file1))
                break;
        }

        fclose(file1);
    }
    return salon;
}

void get_s_helper(int first_entry_address) //работа с файлом SP
{
    if (first_entry_address == -1)
        return;
    FILE* file1;

    if (fopen_s(&file1, "SP.fl", "rb"))
        perror("Error");
    else
    {
        selling str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(selling), 1, file1);
            if (feof(file1))
                break;
            if (str1.course_number == first_entry_address && str1.availability)
            {
                cout << "Course number: " << str1.course_number << endl;
                cout << "id teacher: " << str1.id_course_dealership << endl;
                cout << "id course: " << str1.id_course << endl;
                cout << "Price: " << str1.cost << endl;
                cout << "Address next line in SP.fl: ";
                if (str1.next_entry_student == -1)
                    cout << "Last line";
                else
                    cout << str1.next_entry_student;
                cout << endl << endl;

                get_s_helper(str1.next_entry_student);
            }
        }
        fclose(file1);
    }


}
selling get_s() //работа с файлом SP
{
    int variable = get_m().first_entry_address;
    get_s_helper(variable); //работа с файлом SP
    int course_number = 0;
    selling str1;
    str1.availability = 0;

    if (variable != -1)
    {
        cout << "Input course number: ";
        cin >> course_number;

        FILE* file1;
        str1.availability = 0;
        if (fopen_s(&file1, "SP.fl", "rb"))
            perror("Error");
        else
        {
            while (!feof(file1))
            {
                fread(&str1, sizeof(selling), 1, file1);
                if (feof(file1))
                    break;
                if (str1.course_number == course_number && str1.availability)
                    break;
            }
            fclose(file1);
        }
    }
    else
        str1.course_number = -1;

    return str1;
}



void update_m()
{
    int b = 0;
    teachers showroom = get_m();
    cout << "What thing you want to refactor?" << endl
         << "1 - Teachers Nem" << endl << "2 - Teachers address" << endl << "_____________________" << endl;
    cin >> b;
    switch (b)
    {
        case 1:
            cout << endl << "Input new Name: " << endl;
            cin >> showroom.name;
            break;
        case 2:
            cout << endl << "Input new Address: " << endl;
            cin >> showroom.address;
            break;
        default:
            cout << "Incorrect number";
            break;
    }
    update_file_S(showroom); //обновляем файл S
}


void update_file_SP(selling& element) //обновляем файл SP
{
    FILE* file1;

    if (fopen_s(&file1, "SP.fl", "rb+"))
        perror("Error");
    else
    {
        fseek(file1, sizeof(selling) * (element.course_number - 1), SEEK_SET);
        fwrite(&element, sizeof(selling), 1, file1);
    }
    fclose(file1);
}

void update_s()
{
    int b = 0;
    selling element = get_s();
    if (element.availability)
    {
        cout << "What thing you want to refactor?" << endl
             << "1 - id course" << endl << "2 - price" << endl << "________" << endl;
        cin >> b;
        switch (b)
        {
            case 1:
                cout << endl << "Input new id: " << endl;
                cin >> element.id_course;
                break;
            case 2:
                cout << endl << "Input new price: " << endl;
                cin >> element.cost;
                break;
            default:
                cout << "Number is Incorrect!";
                break;
        }
        update_file_SP(element); //обновляем файл S
    }
}


int ex_5_helper(int first_entry_address)
{
    int count = 1;
    if (first_entry_address == -1)
        return 0;

    FILE* file1;
    if (fopen_s(&file1, "SP.fl", "rb"))
        perror("Error");
    else
    {
        selling str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(selling), 1, file1);
            if (feof(file1))
                break;
            if (str1.course_number == first_entry_address && str1.availability)
                count += ex_5_helper(str1.next_entry_student);
        }
        fclose(file1);
    }
    return count;
}


void ex_5()
{
    int count1 = 0;
    FILE* file1;
    if (fopen_s(&file1, "S.fl", "rb"))
        perror("Error");
    else
    {
        teachers str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(teachers), 1, file1);
            if (feof(file1))
                break;
            if (str1.availability)
                count1++;
        }
    }
    fclose(file1);
    cout << "Quantity teachers: " << count1 << endl;

    int count2 = 0;
    FILE* file2;
    if (fopen_s(&file2, "SP.fl", "rb"))
        perror("Error");
    else
    {
        selling str1;
        while (!feof(file2))
        {
            fread(&str1, sizeof(selling), 1, file2);
            if (feof(file2))
                break;
            if (str1.availability)
                count2++;
        }
    }
    fclose(file2);
    cout << "quantity sales: " << count2 << endl;

    //int count3 = 0;
    if (fopen_s(&file1, "S.fl", "rb"))
        perror("Error");
    else
    {
        teachers str1;
        while (!feof(file1))
        {
            fread(&str1, sizeof(teachers), 1, file1);
            if (feof(file1))
                break;
            if (str1.availability)
            {
                cout << "Quantity students teacher with id " << str1.id_course_dealership << ": ";
                cout << ex_5_helper(str1.first_entry_address) << endl;
            }
        }
    }
    fclose(file1);

}

void del_s(selling s_delete)
{
    if (s_delete.course_number != -1)
    {
        FILE* file1;
        if (fopen_s(&file1, "S.fl", "rb"))
            perror("Error");
        else
        {
            teachers str1;
            while (!feof(file1))
            {
                fread(&str1, sizeof(teachers), 1, file1);
                if (feof(file1))
                    break;
                if (str1.id_course_dealership == s_delete.id_course_dealership && str1.first_entry_address == s_delete.course_number)
                {
                    str1.first_entry_address = s_delete.next_entry_student;
                    break;
                }
            }
            fclose(file1);
            update_file_S(str1); //обновляем файл S
        }
        s_delete.availability = 0;
        update_file_SP(s_delete);

        /*
        FILE* file2;
        if (fopen_s(&file2, "SP.fl", "rb+"))
            perror("Error");
        else
        {
            selling str;
            while (!feof(file2))
            {
                fread(&str, sizeof(selling), 1, file2);
                if (str.course_number == s_delete.course_number)
                {
                    fseek(file2, sizeof(selling) * (str.course_number - 1), SEEK_SET);
                    str.availability = 0;
                    fwrite(&str, sizeof(selling), 1, file2);
                }
                if (feof(file2))
                    break;
            }
        }
        fclose(file2);
        */

    }
}

void del_m()
{
    teachers salon = get_m();

    FILE* file1;
    int count = 0;
    if (fopen_s(&file1, "SP.fl", "rb"))
        perror("Error");
    else
    {
        selling str;
        while (!feof(file1))
        {
            fread(&str, sizeof(selling), 1, file1);
            if (feof(file1))
                break;
            if (salon.id_course_dealership == str.id_course_dealership && str.availability)
                count++;
        }
        fclose(file1);
    }

    selling str;
    while (count)
    {
        if (fopen_s(&file1, "SP.fl", "rb"))
            perror("Error");
        else
        {
            while (!feof(file1))
            {
                fread(&str, sizeof(selling), 1, file1);
                if (feof(file1))
                    break;
                if (salon.id_course_dealership == str.id_course_dealership && str.availability)
                    break;
            }
            fclose(file1);
            del_s(str);
            count--;
        }
    }

    //удаляем из таблицы ind
    if (fopen_s(&file1, "S.ind", "rb+"))
        perror("Error");
    else
    {
        index_table str;
        fseek(file1, sizeof(index_table) * (salon.course_number - 1), SEEK_SET);
        fread(&str, sizeof(index_table), 1, file1);
        fseek(file1, sizeof(index_table) * (salon.course_number - 1), SEEK_SET);
        str.availability = 0;
        fwrite(&str, sizeof(index_table), 1, file1);
    }
    fclose(file1);

    //удаляем из файла S.fl
    if (fopen_s(&file1, "S.fl", "rb+"))
        perror("Error");
    else
    {
        teachers str;
        fseek(file1, sizeof(teachers) * (salon.course_number - 1), SEEK_SET);
        fread(&str, sizeof(teachers), 1, file1);
        fseek(file1, sizeof(teachers) * (salon.course_number - 1), SEEK_SET);
        str.availability = 0;
        fwrite(&str, sizeof(teachers), 1, file1);
    }
    fclose(file1);
}

// физическое удаление логические удаленных данных из всех файлов (функция нигде не исользуется)
void complete_delete()
{

    FILE* file1;
    FILE* file2;

    //из файла S.fl
    if (fopen_s(&file1, "S.fl", "rb") || fopen_s(&file2, "S.fl_copy", "wb"))
        perror("Error");
    else
    {
        teachers str;
        while (!feof(file1))
        {
            fread(&str, sizeof(teachers), 1, file1);
            if (feof(file1))
                break;
            fwrite(&str, sizeof(teachers), 1, file2);
        }
        fclose(file1);
        fclose(file2);
    }
    if (fopen_s(&file1, "S.fl", "wb") || fopen_s(&file2, "S.fl_copy", "rb"))
        perror("Error");
    else
    {
        teachers str;
        while (!feof(file2))
        {
            fread(&str, sizeof(teachers), 1, file2);
            if (feof(file2))
                break;
            if (str.availability)
                fwrite(&str, sizeof(teachers), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
    remove("S.fl_copy");


    //удаляем из таблицы ind
    if (fopen_s(&file1, "S.ind", "rb") || fopen_s(&file2, "S.ind_copy", "wb"))
        perror("Error");
    else
    {
        index_table str;
        while (!feof(file1))
        {
            fread(&str, sizeof(index_table), 1, file1);
            if (feof(file1))
                break;
            fwrite(&str, sizeof(index_table), 1, file2);
        }
        fclose(file1);
        fclose(file2);
    }

    if (fopen_s(&file1, "S.ind", "wb") || fopen_s(&file2, "S.ind_copy", "rb"))
        perror("Error");
    else
    {
        index_table str;
        while (!feof(file2))
        {
            fread(&str, sizeof(index_table), 1, file2);
            if (feof(file2))
                break;
            if (str.availability)
                fwrite(&str, sizeof(index_table), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
    remove("S.ind_copy");


    //удаляем из файла SP.fl
    if (fopen_s(&file1, "SP.fl", "rb") || fopen_s(&file2, "SP.fl_copy", "wb"))
        perror("Error");
    else
    {
        selling str;
        while (!feof(file1))
        {
            fread(&str, sizeof(selling), 1, file1);
            if (feof(file1))
                break;
            fwrite(&str, sizeof(selling), 1, file2);
        }
        fclose(file1);
        fclose(file2);
    }

    if (fopen_s(&file1, "SP.fl", "wb") || fopen_s(&file2, "SP.fl_copy", "rb"))
        perror("Error");
    else
    {
        selling str;
        while (!feof(file2))
        {
            fread(&str, sizeof(selling), 1, file2);
            if (feof(file2))
                break;
            if (str.availability)
                fwrite(&str, sizeof(selling), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
    remove("SP.fl_copy");
}


int main()
{
    setlocale(LC_ALL, "Russian");

    //ЗАГОТОВКА
    cout << "Registration teachers" << endl;
    for (int i = 0; i < 5; i++)
        insert_m();

    cout << "Registration student buys" << endl;
    for (int i = 0; i < 6; i++)
        insert_s();

    ut_m();
    ut_s();

    cout << "Deleting teacher" << endl;
    del_m();

    cout << "Deleting student" << endl;
    del_s(get_s());

    ut_m();
    ut_s();

    cout << "Registration teacher" << endl;
    insert_m();
    cout << "stration student buy:" << endl;
    insert_s();

    ut_m();
    ut_s();

    cout << "Upgrade field teacher" << endl;
    update_m();
    cout << "Upgrade field sales" << endl;
    update_s();

    ut_m();
    ut_s();

    cout << "All lines quantity" << endl;
    ex_5();

}