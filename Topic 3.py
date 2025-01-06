class MenuItem:
    def __init__(self, name, price):
        self.name = name
        self.price = price
        self.next = None

class MenuList:
    def __init__(self):
        self.head = None
    
    def add_dish(self, name, price):
        new_dish = MenuItem(name, price)
        new_dish.next = self.head
        self.head = new_dish
    
    def remove_dish(self, name):
        current = self.head
        if current and current.name == name:
            self.head = current.next
            return
        while current and current.next:
            if current.next.name == name:
                current.next = current.next.next
                return
            current = current.next
    
    def display_menu(self):
        current = self.head
        print("\nMenu Linked List Structure:")
        while current:
            next_name = current.next.name if current.next else "None"
            print(f"[{current.name}: ${current.price}] -> {next_name}")
            current = current.next
menu = MenuList()

menu.add_dish("Posho", 10.99)   
menu.add_dish("Beans", 8.99)   
menu.add_dish("Rice", 12.99)    

print("Initial menu structure:")
menu.display_menu()

menu.remove_dish("Rice")

print("\nAfter removing Rice:")
menu.display_menu()