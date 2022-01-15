"""
Calculates the mean and median of the given temperatures and prints which of
the temperatures are over and which under the median. 
"""


def main():

    TEMPERATURES = ask_the_temperatures()

    MEAN = calculate_mean(TEMPERATURES)
    MEDIAN = calculate_median(TEMPERATURES)

    print(f"Temperature mean: {MEAN:.1f}C")
    print(f"Temperature median: {MEDIAN:.1f}C")
    over_the_median(MEDIAN,MEAN,TEMPERATURES)
    under_median(MEDIAN,MEAN,TEMPERATURES)





def ask_the_temperatures():
    """
    Asks how many days has the temperature been noted from and then asks the
    temperatures in order and adds them in to a list.
    :param number_of_days: int, the wanted amount of days
    :param day, int, the number of the day the temperature is asked from
    :return: list, the given temperatures in order
    """
    list = []
    number_of_days = int(input("Enter amount of days: "))

    for day in range(1,number_of_days+1):

        temp = float(input(f"Enter day {day}. temperature in Celcius: "))
        list.append(temp)

    return list

def calculate_mean(temp_list):
    """
    Calculates the mean of the given temperatures
    :param temp_list: list, the original temperature list
    :param sorted_list: list, the original list sorted in a rising order
    :return: float, the mean of the list
    """
    length=len(temp_list)
    mean=sum(temp_list)/length

    return mean

def calculate_median(temp_list):
    """
    Calculates the median of the given temperatures
    :param temp_list: list, the original temperature list
    :param sorted_list: list, the original list sorted in a rising order
    :return: float, the median of the list
    """

    sorted_list = sorted(temp_list)
    length=len(sorted_list)

    if length % 2 == 0:
        index = length//2
        value1 = sorted_list[index]
        value2 = sorted_list[index-1]
        median = (value1+value2) / 2

        return median

    else:
        median = sorted_list[length//2]

        return median


def over_the_median(median,mean,temp_list):
    """
    Finds out which of the parameters on the list are over the median
    and prints them and the day in order.
    :param median: float, the median of temp_list
    :param mean: float, the mean of temp_list
    :param temp_list: list, the given temperatures

    """


    print("Over or at median were:")
    length = len(temp_list)
    over_median = []
    index = 0
    while index < length:

        temp = temp_list[index]

        if temp >= median:
            over_median.append(temp)
            print(f"Day {(index + 1):2}. {temp:5.1f}C difference to mean: \
{(-(mean)-(-temp)):5.1f}C")
            index += 1

        else:
            index += 1




def under_median(median,mean,temp_list):
    """
    Finds out which of the parameters on the list are under the median
    and prints them and the day in order.
    :param median: float, the median of temp_list
    :param mean: float, the mean of temp_list
    :param temp_list: list, the given temperatures

    """
    print("Under median were:")

    length = len(temp_list)
    under_median = []
    index = 0
    while index < length:

        temp = temp_list[index]

        if temp < median:
            under_median.append(temp)
            print(f"Day {(index+1):2}. {temp:5.1f}C difference to mean: \
{(-(mean)-(-temp)):5.1f}C")

            index += 1
        else:
            index += 1





if __name__=="__main__":
    main()