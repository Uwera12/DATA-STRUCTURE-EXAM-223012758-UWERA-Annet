
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Deque:
    def __init__(self):
        self.items = []
    
    def is_empty(self):
        """Check if deque is empty"""
        return len(self.items) == 0
    
    def add_front(self, item):
        """Add an item to the front of deque"""
        self.items.insert(0, item)
    
    def add_rear(self, item):
        """Add an item to the rear of deque"""
        self.items.append(item)
    
    def remove_front(self):
        """Remove and return the front item"""
        if not self.is_empty():
            return self.items.pop(0)
        return None
    
    def remove_rear(self):
        """Remove and return the rear item"""
        if not self.is_empty():
            return self.items.pop()
        return None
    
    def peek_front(self):
        """View the front item without removing it"""
        if not self.is_empty():
            return self.items[0]
        return None
    
    def peek_rear(self):
        """View the rear item without removing it"""
        if not self.is_empty():
            return self.items[-1]
        return None

class CircularLinkedList:
    def __init__(self):
        self.head = None
    
    def is_empty(self):
        """Check if list is empty"""
        return self.head is None
    
    def append(self, data):
        """Add a new node at the end of the list"""
        new_node = Node(data)
        
        if self.is_empty():
            self.head = new_node
            new_node.next = self.head
            return
        
        current = self.head
        while current.next != self.head:
            current = current.next
            
        current.next = new_node
        new_node.next = self.head
    
    def display(self):
        """Display all items in the list"""
        if self.is_empty():
            return "List is empty"
        
        items = []
        current = self.head
        
        while True:
            items.append(str(current.data))
            current = current.next
            if current == self.head:
                break
                
        return " -> ".join(items) + " -> (back to start)"
    
    def delete(self, data):
        """Delete a node with the given data"""
        if self.is_empty():
            return
        
        if self.head.data == data:
            if self.head.next == self.head:
                self.head = None
            else:
                current = self.head
                while current.next != self.head:
                    current = current.next
                current.next = self.head.next
                self.head = self.head.next
            return
        
        current = self.head
        prev = None
        while current.next != self.head:
            if current.data == data:
                prev.next = current.next
                return
            prev = current
            current = current.next
        
        if current.data == data:
            prev.next = self.head

def menu_system_example():
    
    daily_specials = Deque()
    
    daily_specials.add_rear("ommellete")
    daily_specials.add_front("chicken soup")
    daily_specials.add_rear("pilawu")
    
    print("Daily Specials:")
    print(f"First special: {daily_specials.peek_front()}")
    print(f"Last special: {daily_specials.peek_rear()}")
    
    menu_items = CircularLinkedList()
    
    menu_items.append("Pizza")
    menu_items.append("Chicken Salad")
    menu_items.append("chips")
    menu_items.append("Beef burger")
    
    print("\nRegular Menu Items:")
    print(menu_items.display())
    
    menu_items.delete("Chicken Salad")
    print("\nAfter removing Chicken Salad:")
    print(menu_items.display())


if __name__ == "__main__":
    menu_system_example()