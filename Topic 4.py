class Order:
    def __init__(self, order_id, items, total):
        self.order_id = order_id
        self.items = items
        self.total = total
        self.next = None

class OrderList:
    def __init__(self, max_orders=5):
        self.head = None
        self.max_orders = max_orders
        self.current_size = 0
    
    def add_order(self, order_id, items, total):
        new_order = Order(order_id, items, total)
        if not self.head:
            self.head = new_order
            self.current_size += 1
            return True
        if self.current_size >= self.max_orders:
            self.remove_oldest_order()
        new_order.next = self.head
        self.head = new_order
        self.current_size += 1
        return True
    
    def remove_oldest_order(self):
        if not self.head:
            return
        if not self.head.next:
            self.head = None
            self.current_size -= 1
            return
        current = self.head
        while current.next.next:
            current = current.next
        current.next = None
        self.current_size -= 1
    
    def display_orders(self):
        current = self.head
        print("\nOrder Linked List Structure:")
        while current:
            next_id = f"Order #{current.next.order_id}" if current.next else "None"
            print(f"[Order #{current.order_id}: {current.items}, ${current.total}] -> {next_id}")
            current = current.next
orders = OrderList(max_orders=3)

print("Adding 3 orders...")
orders.add_order(1, ["Cabbage", "G.nuts"], 2000)
orders.add_order(2, ["Cassava", "Milk"], 1500)
orders.add_order(3, ["Maize", "Soup"], 2200)
orders.display_orders()

print("\nAdding Order #4 (will remove oldest order)...")
orders.add_order(4, ["Beer", "Meat"], 3000)
orders.display_orders()