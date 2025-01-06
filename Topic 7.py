class MenuItem:
    def __init__(self, name, price=None, priority=None):
        self.name = name
        self.price = price
        self.priority = priority
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

       
        print(f'{prefix}{self.name}{" - $" + str(self.price) if self.price else ""} (Priority: {self.priority})')

        
        for i, child in enumerate(self.children):
            child.display(level + 1, is_last=(i == len(self.children) - 1))


def counting_sort(menu_items):
    if not menu_items:
        return []

    
    max_priority = max(item.priority for item in menu_items)

    count = [0] * (max_priority + 1)

   
    for item in menu_items:
        count[item.priority] += 1

    
    sorted_items = []
    for priority in range(max_priority + 1):
        for item in menu_items:
            if item.priority == priority:
                sorted_items.append(item)

    return sorted_items


def create_menu():
    
    main_menu = MenuItem('Main Menu')

    appetizers = MenuItem('Appetizers')
    main_menu.add_child(appetizers)

    drinks = MenuItem('Drinks')
    main_menu.add_child(drinks)

    desserts = MenuItem('Desserts')
    main_menu.add_child(desserts)

    appetizers.add_child(MenuItem('Akabanga', 5, priority=2))
    appetizers.add_child(MenuItem('KETCHUP', 3, priority=1))

    drinks.add_child(MenuItem('Novida', 2, priority=3))
    drinks.add_child(MenuItem('Twist', 2.5, priority=2))

    desserts.add_child(MenuItem('Chocolate Cake', 4, priority=1))
    desserts.add_child(MenuItem('Ice Cream', 3, priority=3))

    return main_menu

def sort_menu_items(menu):
    for category in menu.children:
        sorted_items = counting_sort(category.children)
        category.children = sorted_items

menu = create_menu()
sort_menu_items(menu)

menu.display()
