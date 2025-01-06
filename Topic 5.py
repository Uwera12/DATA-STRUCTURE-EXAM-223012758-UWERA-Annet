class MenuItem:
    def __init__(self, name, price, category):
        self.name = name
        self.price = price
        self.category = category
        self.next = None  

class DigitalMenu:
    def __init__(self):
        self.head = None 


    def add_item(self, name, price, category):
        new_item = MenuItem(name, price, category)
        if not self.head:
            self.head = new_item
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_item

    def remove_item(self, name):
        current = self.head
        previous = None
        while current and current.name != name:
            previous = current
            current = current.next
        if current: 
            if previous:
                previous.next = current.next
            else:
                self.head = current.next
            print(f"Item '{name}' removed.")
        else:
            print(f"Item '{name}' not found.")

    def display_menu(self):
        if not self.head:
            print("Menu is empty.")
            return
        current = self.head
        print("Digital Menu:")
        while current:
            print(f"- {current.name} (${current.price:.2f}) [{current.category}]")
            current = current.next

menu = DigitalMenu()
menu.add_item("Gaot meat", 50.4, "Main Beff")
menu.add_item("Chapati", 2.99, "Snacks")
menu.add_item("African tea", 1.99, "Drinks")

menu.display_menu()

menu.remove_item("Chapati")
menu.display_menu()
