
class MyAVLtree {

    private static final int INVALID_INDICATOR = -1;
    private Node root;

    public MyAVLtree() {
        root = null;
    }

    public class Node {
        int number;
        Node left, right, parent;
        int height;

        public Node(int number) {
            this.number = number;
            left = right = parent = null;
            height = 1;
        }
    }

    int nodeHeight(Node node) {
        if (node == null)
            return 0;
        return node.height;
    }

    Node rotLeft(Node node) {

        Node y = node.right;

        Node Tree1 = node.left;
        Node Tree2 = y.left;


        y.left = node;
        node.right = Tree2;

        node.height = Math.max(nodeHeight(node.left), nodeHeight(node.right) + 1);
        y.height = Math.max(nodeHeight(y.left), nodeHeight(y.right) + 1);

        return y;   // now this is the root of the subtree

    }

    Node rotRight(Node node) {

        Node y = node.left;

        Node Tree3 = y.right;


        y.right = node;
        node.left = Tree3;

        node.height = Math.max(nodeHeight(node.left), nodeHeight(node.right) + 1);
        y.height = Math.max(nodeHeight(y.left), nodeHeight(y.right) + 1);

        return y;   // now this is the root of the subtree


    }

    public void insert(int number) {
        root = insertUtil(root, number);
    }


    public Node insertUtil(Node currNode, int number) {

        if (currNode == null) {

//            System.out.println("root is null");
            return (new Node(number));
        }

        if (number < currNode.number) {
            // traverse the left subtree
            currNode.left = insertUtil(currNode.left, number);
        } else if (number > currNode.number) {
            currNode.right = insertUtil(currNode.right, number);
        } else {
            // then the value must already in the AVL tree
            return currNode;
        }


        currNode.height = Math.max(nodeHeight(currNode.left), nodeHeight(currNode.right)) + 1;

        // checking if the parent gets unbalanced after insertion
        int balanceFactor;
        if (currNode == null) {
            balanceFactor = 0;
        } else {
            balanceFactor = nodeHeight(currNode.left) - nodeHeight(currNode.right);
        }
//        System.out.println("balance factor " + balanceFactor);

        if (Math.abs(balanceFactor) > 1) {
            // currNode is the node that violates height property
            // we stumble upon this unbalanced node in some of our recursive calls
            return reBalanceAVL(balanceFactor, currNode);
        }

//        System.out.println(number + " inserted successfully");
        return currNode;

    }

    private Node reBalanceAVL(int balanceFactor, Node currNode) {
        // now let's handle all the cases of unbalanced situation
        // zig zig (left inclined)
        if (balanceFactor > 1 && getBalanceFactor(currNode.left) >= 0)
            return rotRight(currNode);

        // zig zag (left right)
        if (balanceFactor > 1 && getBalanceFactor(currNode.left) < 0) {
            currNode.left = rotLeft(currNode.left);
            return rotRight(currNode);
        }

        // zig zig (right inclined)
        if (balanceFactor < -1 && getBalanceFactor(currNode.right) <= 0)
            return rotLeft(currNode);

        // zig zag (right left)
        if (balanceFactor < -1 && getBalanceFactor(currNode.right) > 0) {
            currNode.right = rotRight(currNode.right);
            return rotLeft(currNode);
        }
        return null;
    }

    public void deleteItem(int number) {

//        if (deleteItemRecursion(this.root, number) == null) {
//            System.out.println(number + " Not found in the BST");
//        } else {
////            System.out.println(number + " Deleted successfully");
//        }
        root = deleteItemRecursion(root, number);
    }

    private Node deleteItemRecursion(Node currNode, int number) {

        if (!search(number, currNode)) {
            //  THE ITEM IS NOT IN THE BST
            return null;
        }

        if (currNode == null) {
            return currNode;
        } else if (number < currNode.number) {
            currNode.left = deleteItemRecursion(currNode.left, number);
        } else if (number > currNode.number) {
            currNode.right = deleteItemRecursion(currNode.right, number);
        } else {
            //  GOT THE DELETABLE NODE
            if (currNode.left == null && currNode.right == null) {
                //  THE NODE HAS NO CHILDREN
                currNode = null;
            } else if (currNode.left == null) {
                //  HAS ONLY RIGHT CHILD
                Node temp = currNode;
                currNode = currNode.right;
                temp = null;
            } else if (currNode.right == null) {
                //  HAS ONLY LEFT CHILD
                Node temp = currNode;
                currNode = currNode.left;
                temp = null;
            } else {
                //  GET THE MIN OF THE RIGHT CHILD OF THE DELETABLE NODE
                //  REPLACE THE MIN NODE WITH THE DELETABLE NODE
                Node minNode = getMinNode(currNode.right);
                int minVal = minNode.number;
                currNode.number = minVal;

                currNode.right = deleteItemRecursion(currNode.right, minVal);
            }
        }

//        ------ old bst delete until now --------------

        if (currNode == null)
            return currNode;

        // updating the node height
        currNode.height = Math.max(nodeHeight(currNode.left), nodeHeight(currNode.right)) + 1;

        // checking if the node gets unbalanced after deletion

        int balanceFact = getBalanceFactor(root);

        if (Math.abs(balanceFact) > 1) {
            // currNode is the node that violates height property
            // we stumble upon this unbalanced node in some of our recursive calls
            return reBalanceAVL(balanceFact, currNode);
        }

        return currNode;

    }

    int getBalanceFactor(Node node) {
        if (node == null)
            return 0;
        return height(node.left) - height(node.right);
    }

    public Node getMinNode(Node root) {

        while (root.left != null) {
            root = root.left;
        }
        return root;
    }


    public void printTree() {
        if (this.root == null) {
            System.out.println("The tree is empty");
            return;
        }
        printPreOrderAVL(this.root);
    }

    private void printPreOrderAVL(Node currRoot) {
        if (currRoot == null)
            return;

        System.out.print(currRoot.number);

        // if currRoot is leaf
        if (currRoot.left == null && currRoot.right == null)
            return;

        // left subtree
        System.out.print("(");
        printPreOrderAVL(currRoot.left);
        System.out.print(")");

        System.out.print("(");
        printPreOrderAVL(currRoot.right);
        System.out.print(")");
    }

    public void searchItem(int number) {
        if (search(number, root)) {
            System.out.println("True");
        } else {
            System.out.println("False");
        }
    }

    private boolean search(int number, Node root) {

        while (root != null) {
            if (root.number == number) {

                return true;
            } else if (root.number < number) {
                //  TRAVERSING THE RIGHT SUBTREE
                root = root.right;

            } else {
                //  TRAVERSING THE LEFT SUBTREE
                root = root.left;
            }
        }
        if (root == null) {

            return false;
        }
        return false;
    }


    public int getInOrderSuccessor(int number) {

        Node bkpRoot = root;
        Node successor[] = new Node[1];
        successor[0] = new Node(-1);
        //  SENDING AN ARRAY OF OBJECT IN ORDER TO PASS THE REFERENCE OF THE SUCCESSOR NODE
        //  AND SEE THE CHANGE GLOBALLY
        inOrderSuccessor(number, root, successor);
        root = bkpRoot;

        return successor[0].number;
    }

    private void inOrderSuccessor(int number, Node currRoot, Node successor[]) {
        if (currRoot == null) {
            return;
        }

        if (currRoot.number == number) {
            if (currRoot.right != null) {
                successor[0] = getMinNode(currRoot.right);
            }

        } else if (currRoot.number > number) {
            successor[0] = currRoot;
            inOrderSuccessor(number, currRoot.left, successor);

        } else {
            inOrderSuccessor(number, currRoot.right, successor);
        }
    }

    public Node getMaxNode(Node root) {
        while (root.right != null) {
            root = root.right;
        }
        return root;
    }

    public int getInOrderPredecessor(int number) {

        Node bkpRoot = root;
        Node predecessor[] = new Node[1];
        predecessor[0] = new Node(-1);
        //  SENDING AN ARRAY OF OBJECT IN ORDER TO PASS THE REFERENCE OF THE PREDECESSOR NODE
        //  AND SEE THE CHANGE GLOBALLY
        inOrderPredecessor(number, root, predecessor);
        root = bkpRoot;

        return predecessor[0].number;
    }

    private void inOrderPredecessor(int number, Node currRoot, Node predecessor[]) {
        if (currRoot == null) {
            return;
        }

        if (currRoot.number == number) {
            if (currRoot.left != null) {
                predecessor[0] = getMaxNode(currRoot.left);

            }

        } else if (currRoot.number > number) {

            inOrderPredecessor(number, currRoot.left, predecessor);

        } else {
            predecessor[0] = currRoot;
            inOrderPredecessor(number, currRoot.right, predecessor);

        }
    }


    public int getItemDepth(int number) {
        return getDepth(number, root);
    }

    private int getDepth(int number, Node root) {

        if (!search(number, root)) {
            return INVALID_INDICATOR;
        }

        if (root == null) {
            return INVALID_INDICATOR;
        }
        int itemDepth = 0;
        while (root != null) {
            if (root.number == number) {
                return itemDepth;
            } else if (root.number < number) {
                //  TRAVERSING THE RIGHT SUBTREE
                root = root.right;
                itemDepth++;

            } else {
                //  TRAVERSING THE LEFT SUBTREE
                root = root.left;
                itemDepth++;
            }
        }
        return itemDepth;
    }

    public int getMinItem() {
        return getMinItem(root);
    }

    private int getMinItem(Node root) {

        while (root.left != null) {
            root = root.left;
        }
        return root.number;
    }

    public int getMaxItem() {
        return maxItem(root);
    }

    private int maxItem(Node root) {

        while (root.right != null) {
            root = root.right;
        }
        return root.number;
    }

    public int getHeightTree() {
        return height(root);
    }

    private int height(Node root) {

        if (root == null)
            return -1;

        int depthLeft = height(root.left);
        int depthRight = height(root.right);

        if (depthLeft > depthRight)
            return depthLeft + 1;
        else
            return depthRight + 1;
    }

    public void printInOrder() {
        inOrderTraversal(root);
    }

    private void inOrderTraversal(Node root) {
        if (root == null)
            return;

        inOrderTraversal(root.left);
        System.out.print(root.number + " ");
        inOrderTraversal(root.right);
    }

    public void printPreOrder() {
        preOrderTraversal(root, true);
    }

    private void preOrderTraversal(Node root, boolean fromLeft) {
        // for offline
        if (root == null)
            return;

        if (fromLeft)
            System.out.print("(" + root.number + " ");
        else
            System.out.print(root.number + ")");
        preOrderTraversal(root.left, true);
        preOrderTraversal(root.right, false);
    }

    public void printPostOrder() {
        postOrderTraversal(root);
    }

    private void postOrderTraversal(Node root) {

        if (root == null)
            return;

        postOrderTraversal(root.left);
        postOrderTraversal(root.right);
        System.out.print(root.number + " ");
    }

    public int getSize() {
        return size(root);
    }

    private int size(Node root) {
        if (root == null)
            return 0;
        else {
            return size(root.left) + size(root.right) + 1;
        }
    }

}