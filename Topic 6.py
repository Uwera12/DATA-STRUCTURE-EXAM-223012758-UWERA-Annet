class MenuItem:
    def __init__(self, name, price=None):
        self.name = name
        self.price = price
        self.children = []  

    def add_child(self, child):
        self.children.append(child)

    def display(self, level=0, is_last=True):
        prefix = '  ' * level
        if level > 0:
            if is_last:
                prefix += '└── '
            else:
                prefix += '├── '

    
        print(f'{prefix}{self.name}{" - $" + str(self.price) if self.price else ""}')
        
        for i, child in enumerate(self.children):
            child.display(level + 1, is_last=(i == len(self.children) - 1))

def create_menu():

    main_menu = MenuItem('Main Menu')

    appetizers = MenuItem('Appetizers')
    main_menu.add_child(appetizers)
    
    drinks = MenuItem('Drinks')
    main_menu.add_child(drinks)
    
    desserts = MenuItem('Desserts')
    main_menu.add_child(desserts)

    appetizers.add_child(MenuItem('Akabanga', 5))
    appetizers.add_child(MenuItem('KETCHUP', 3))

    drinks.add_child(MenuItem('Novida', 2))
    drinks.add_child(MenuItem('Twist', 2.5))

    desserts.add_child(MenuItem('Chocolate Cake', 4))
    desserts.add_child(MenuItem('Ice Cream', 3))

    return main_menu

menu = create_menu()
menu.display()
