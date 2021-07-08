import sys

order = 3

max_val = order
max_keys = order-1

class node:
    def __init__(self):
        self.count = 0

        self.keys = []
        self.ptr = []

    def __str__(self, space=""):
        str_count = space + "Count: " + str(self.count) + "\n"
        str_keys = space + "Keys : " + str(self.keys) + "\n"

        ptr_flags = [True] * len(self.ptr)
        str_ptr = space + "Ptrs : " + str(ptr_flags) + "\n"

        rtn_str = str_count + str_keys + str_ptr
        return rtn_str

    def insert(self, input_key, left, right):
        
        self.count += 1
        rtn_flag = self.count > max_keys

        idx = 0        
        while idx<len(self.keys) and self.keys[idx]<input_key:
            idx+=1

        if len(self.keys) == 0:
            self.keys.append(input_key)
            
            self.ptr.append(left)
            self.ptr.append(right)

        elif idx<len(self.keys):
            
            self.keys.insert(idx, input_key)
            
            self.ptr[idx] = left
            self.ptr.insert(idx+1, right)
        
        else:
            self.keys.append(input_key)

            self.ptr[idx] = left
            self.ptr.append(right)

        return rtn_flag       

class leaf:
    def __init__(self):
        self.count = 0

        self.keys = []
        self.values = []

        self.nextleaf = None
        self.prevleaf = None

    def __str__(self, space=""):        
        str_count = space + "count : " + str(self.count) + "\n"
        str_keys = space + "keys  : " + str(self.keys) + "\n"
        str_values = space + "values: " + str(self.values) + "\n"

        next_leaf_keys_str = str([])
        if self.nextleaf is not None:
            next_leaf_keys_str = str(self.nextleaf.keys)

        str_nextleaf = space + "nextleaf: " + str(self.nextleaf is not None) + "-" + next_leaf_keys_str + "\n"
        
        rtn_str = str_count + str_keys + str_values + str_nextleaf
        return rtn_str

    def insert(self, input_key):
        
        flag, idx = find(self.keys, input_key)
        if flag == True:
            self.values[idx] += 1
            return False
        
        idx = 0        
        while idx<len(self.keys) and self.keys[idx]<input_key:
            idx+=1

        if idx<len(self.keys):
            self.keys.insert(idx, input_key)
            self.values.insert(idx, 1)
        else:
            self.keys.append(input_key)
            self.values.append(1)

        self.count += 1

        if self.count > max_keys:
            return True
        else:
            return False

class btree:
    def __init__(self):
        self.root = leaf()      

    # Split fun
    def split_leaf(self, root):
        left = leaf()
        right = leaf()

        if root.prevleaf is not None:
            root.prevleaf.nextleaf = left
        
        if root.nextleaf is not None:
            root.nextleaf.prevleaf = right

        left.nextleaf = right
        right.nextleaf = root.nextleaf

        left.prevleaf = root.prevleaf
        right.prevleaf = left

        left.count = int(order/2)
        right.count = order - left.count

        left.keys = root.keys[:left.count]
        right.keys = root.keys[left.count:]                
        
        left.values = root.values[:left.count]
        right.values = root.values[left.count:]
        
        return right.keys[0], left, right

    def split_node(self, root):
        left = node()
        right = node()
        
        left.count = int(order/2)
        right.count = order - left.count - 1

        left.keys = root.keys[:left.count]
        right.keys = root.keys[left.count+1:]          

        left.ptr = root.ptr[:left.count+1]      
        right.ptr = root.ptr[left.count+1:]      

        return root.keys[left.count], left, right

    # find link where to insert
    def find_ptr(self, root, input_key):
        idx = 0
        while idx<len(root.keys) and root.keys[idx]<=input_key:
            idx+=1

        return root.ptr[idx]

    #insert
    def insert_helper(self, root, input_key):
        if is_leaf(root) == True:

            need_split = root.insert(input_key)
            if need_split == True:
                key, left, right = self.split_leaf(root)
                return True, key, left, right

        else:

            ptr = self.find_ptr(root, input_key)
            need_of_insert, key, left, right = self.insert_helper(ptr, input_key)

            if need_of_insert == True:
                need_split = root.insert(key, left, right)

                if need_split == True:
                    key, left, right = self.split_node(root)
                    return True, key, left, right

        return False, -1, None, None

    def insert(self, input_key):

        if is_leaf(self.root) == True:

            need_split = self.root.insert(input_key)
            if need_split == True:
                key, left, right = self.split_leaf(self.root)

                self.root = node()
                _ = self.root.insert(key, left, right)  

        else:

            ptr = self.find_ptr(self.root, input_key)
            need_of_insert, key, left, right = self.insert_helper(ptr, input_key)

            if need_of_insert == True:
                need_split = self.root.insert(key, left, right)

                if need_split == True:
                    key, left, right = self.split_node(self.root)
                    
                    self.root = node()
                    _ = self.root.insert(key, left, right)

    # display
    def display_helper(self, root, space=""):
        print(root.__str__(space))

        if is_leaf(root) == False:
            for p in root.ptr:
                self.display_helper(p, space + "\t")
            
    def display(self):
        self.display_helper(self.root, "")

    # find
    def find(self, input_key):

        root = self.root
        while is_leaf(root) == False:

            idx = 0
            while idx<len(root.keys) and root.keys[idx]<=input_key:
                idx+=1

            root = root.ptr[idx]

        flag, idx = find(root.keys, input_key)
        if flag==True:
            return "YES"
        return "NO"            

    # count
    def count(self, input_key):

        root = self.root
        while is_leaf(root) == False:

            idx = 0
            while idx<len(root.keys) and root.keys[idx]<=input_key:
                idx+=1

            root = root.ptr[idx]

        flag, idx = find(root.keys, input_key)
        
        if flag == True:
            return root.values[idx]
        return 0

    # range
    def range(self, left_range, right_range):
        root = self.root
        while is_leaf(root) == False:

            idx = 0
            while idx<len(root.keys) and root.keys[idx]<=left_range:
                idx+=1

            root = root.ptr[idx]

        count = 0
        for idx, key in enumerate(root.keys):
            if key >= left_range and key<= right_range: 
                count += root.values[idx]

        root = root.nextleaf

        while True:
            if root is None:
                break
                        
            for idx, key in enumerate(root.keys):
                if key<= right_range: 
                    count += root.values[idx]
                else:
                    break
                    
            root = root.nextleaf

        return count

def find(input_list, val):
    try:
        idx = input_list.index(val)
        return True, idx
    except ValueError:
        return False, -1

def is_leaf(root):
    return isinstance(root, leaf)

if __name__ == "__main__":

    input_file_name = sys.argv[1]
    # input_file_name = "input1.txt"

    input_file = open(input_file_name, 'r')
    commands = input_file.read().split("\n")
    input_file.close()

    output = []

    mytree = btree()
    for cmd in commands:
        cmd_literals = cmd.split()
        # print(cmd_literals)

        if len(cmd_literals) == 0:
            continue
        
        if cmd_literals[0].upper() == "INSERT":
            key = int(cmd_literals[1])
            mytree.insert(key)
        
        elif cmd_literals[0].upper() == "FIND":
            key = int(cmd_literals[1])
            ans = mytree.find(key)
            
            print(ans)
            output.append(str(ans) + "\n")

        elif cmd_literals[0].upper() == "COUNT":
            key = int(cmd_literals[1])
            ans = mytree.count(key)
            
            print(ans)
            output.append(str(ans) + "\n")
        
        elif cmd_literals[0].upper() == "RANGE":
            left = int(cmd_literals[1])
            right = int(cmd_literals[2])
            ans = mytree.range(left, right)
            
            print(ans)
            output.append(str(ans) + "\n")

        else:
            # mytree.display()   
            print("")

    # mytree.display()

    output_file_name = sys.argv[2]
    # output_file_name = "out.txt"


    output_file = open(output_file_name, 'w')
    commands = output_file.writelines(output)
    output_file.close()
