import tools

while True:
    # print menu
    tools.show_menu()
    option = input("Please enter option: ")

    if option in ["1", "2", "3"]:
        # new name card
        if option == "1":
            tools.new_card()
            print("")

        # print all name cards
        elif option == "2":
            tools.show_card()

        # read name card
        elif option == "3":
            tools.search_card()
            print("")

    elif option == "0":
        print("Bye bye")
        break
    else:
        print("Wrong input, please try again")
