# store name card
card_list = []


def show_menu():
    """Show menu"""
    print("*" * 50)
    print("Welcome to name card system")
    print("1. Add mame card")
    print("2. Show all name card")
    print("3. Search name card")
    print("0. Exit")
    print("*" * 50)


def new_card():
    """Add a new name card"""
    print("Add a name card")
    name_str = input("Please enter a name: ")
    phone_str = input("Please input phone number: ")
    email_str = input("Please input email address: ")

    card_dict = {"name": name_str,
                 "phone": phone_str,
                 "email": email_str}

    card_list.append(card_dict)
    print(card_list)
    print("%s 's name card added" % name_str)


def show_card():
    """Show all name card"""
    if len(card_list) == 0:
        print("No name card in card list, please add new card")
        return

    print("Show all name card: ")
    for category in ["Name", "Phone", "Email"]:
        print(category, end="\t\t\t")

    print("")
    print("-" * 50)
    for name_card in card_list:
        print("%s\t\t\t%s\t\t%s" % (name_card["name"],
                                    name_card["phone"],
                                    name_card["email"]))

    print("")


def search_card():
    """search name card by name"""
    print("Search name card by name")
    find_name = input("Please enter a name: ")
    for name_card in card_list:
        if name_card["name"] == find_name:
            for category in ["Name", "Phone", "Email"]:
                print(category, end="\t\t\t")

            print("")
            print("-" * 50)
            print("%s\t\t\t%s\t\t%s" % (name_card["name"],
                                        name_card["phone"],
                                        name_card["email"]))
            # Modify name card
            deal_card(name_card)
            break
    else:
        print("%s does not exists" % find_name)


def deal_card(name_card):
    """Modify name card"""
    print("1. Modify")
    print("2. Delete")
    print("0. Return")
    option = input("Please enter options: ")
    if option == "1":
        name_card["name"] = input("Please enter new name: ")
        name_card["phone"] = input("Please enter new phone: ")
        name_card["email"] = input("Please enter new email: ")
        print("The name card is modified")
    elif option == "2":
        card_list.remove(name_card)
        print("%s 's name card is deleted" % name_card["name"])
    elif option == "0":
        pass
    else:
        print("Wrong input, please try again")


