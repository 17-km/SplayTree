#include "SplayTree.h"

// funkcja do tworzenia nowego wezla, jako argument pobiera jego wartosc,
// ustawia wskazniki do dzieci na null a wartosc na podana w argumencie funkcji
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// funkcja do rotacji drzewa w prawo
// ustawia jako korzen pierwszy wezel po lewej stronie
struct Node* rightRotate(struct Node* root)
{
    struct Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// funkcja do rotacji drzewa w lewo
// ustawia jako korzen pierwszy wezel po prawej stronie
struct Node* leftRotate(struct Node* root)
{
    struct Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

// funkcja splay do wywolania przy wyszukaniu/wstawieniu/usunieciu wezla
// ustawia wezel zawierajacy klucz jako korzen
struct Node* splay(struct Node* root, int key)
{
    // specjalne przypadki dla pustego drzewa lub kiedy klucz ju¿ jest w korzeniu
    if (root == NULL || root->key == key)
        return root;

    // jeœli klucz jest mniejszy od klucza korzenia, to szukamy w lewym poddrzewie
    if (root->key > key)
    {
        // jeœli lewy syn jest pusty, to zwroc korzen - brak wartosci w drzewie
        if (root->left == NULL) return root;

        // jeœli klucz jest mniejszy od klucza lewego syna, schodzimy dalej w kolejnego lewego potomka
        if (root->left->key > key)
        {
            // wywolujemy funkcje splay podajac jako korzen kolejnego lewego potomka
            root->left->left = splay(root->left->left, key);

            // obracamy drzewem w prawo, tak by kolejny lewy potomek stal sie pierwszym lewym potomkiem korzenia
            root = rightRotate(root);
        }

        // jeœli klucz jest wiekszy od klucza lewego syna, schodzimy dalej w kolejnego prawego potomka
        else if (root->left->key < key)
        {
            // wywolujemy funkcje splay podajac jako korzen kolejnego prawego potomka
            root->left->right = splay(root->left->right, key);

            // jeœli ten kolejny prawy potomek istnieje, to obracamy poddrzewem, ktorego korzeniem jest pierwszy lewy potomek korzenia
            // tak by ten kolejny prawy potomek stal sie pierwszym lewym potomkiem korzenia
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // obrot drzewa w prawo tak by lewy potomek by³ teraz korzeniem
        return (root->left == NULL)? root: rightRotate(root);
    }
    // jeœli klucz jest wiekszy od klucza korzenia, to szukamy w prawym poddrzewie
    else
    {
        // jeœli prawy syn jest pusty, to zwroc korzen - brak wartosci w drzewie
        if (root->right == NULL) return root;

        // jeœli klucz jest wiekszy od klucza prawego syna, schodzimy dalej w kolejnego prawego potomka
        if (root->right->key < key)
        {
            // wywolujemy funkcje splay podajac jako korzen kolejnego prawego potomka
            root->right->right = splay(root->right->right, key);

            // obracamy drzewem w lewo, tak by kolejny prawy potomek stal sie pierwszym prawym potomkiem korzenia
            root = leftRotate(root);
        }

        // jeœli klucz jest mniejszy od klucza prawego syna, schodzimy dalej w kolejnego lewego potomka
        else if (root->right->key > key)
        {
            // wywolujemy funkcje splay podajac jako korzen kolejnego lewego potomka
            root->right->left = splay(root->right->left, key);

            // jeœli ten kolejny lewy potomek istnieje, to obracamy poddrzewem, ktorego korzeniem jest pierwszy prawy potomek korzenia
            // tak by ten kolejny lewy potomek stal sie pierwszym prawym potomkiem korzenia
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }

        // obrot drzewa w lewo tak by prawy potomek by³ teraz korzeniem
        return (root->right == NULL)? root: leftRotate(root);
    }
}

// funkcja do wstawiania nowego klucza
struct Node* insertNode(struct Node* root, int key)
{
    // wstawianianie klucza gdy drzewo jest puste
    if (root == NULL) return newNode(key);

    // ustawienie wezla zawierajacego wartosc podanego klucza na poczatek
    root = splay(root, key);

    // jeœli klucz ju¿ istnieje, to odpowiasdajacy mu wezel bedzie teraz korzeniem
    // zwraca root, bez dodawaniua klucza ponownie
    if (key == root->key) return root;

    // tworzenie nowego wezla i wstawianie go jako korzen
    struct Node* newnode  = newNode(key);

    // jeœli klucz jest mniejszy od klucza starego korzenia, to dodaj stary korzen jako lewy syn nowego
    if (root->key > key)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }

    // jeœli klucz jest wiekszy od klucza starego korzeniaa, to dodaj stary korzen jako prawy syn nowego
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    // zwroc nowy korzen
    return newnode;
}

// funkcja do usuwania klucza
struct Node* deleteNode(struct Node* root, int key)
{
    // jesli drzewo jest puste to zwracamy null
    if (root == NULL) return NULL;

    // ustawienie wezla zawierajacego wartosc podanego klucza na poczatek
    root = splay(root, key);

    // jeœli klucz ju¿ istnieje, to odpowiasdajacy mu wezel bedzie teraz korzeniem
    // jeœli klucz nie istnieje w drzewie, to zwroc bez usuwania
    if (key != root->key) return root;

    // jeœli korzen nie ma ¿adnego syna, to usun
    if (!root->left && !root->right)
    {
        free(root);
        return NULL;
    }

    // jeœli korzen ma tylko jednego syna, to usun go i zwroc jego syna jako korzen
    if (!root->left)
    {
        struct Node *newRoot = root->right;
        free(root);
        return newRoot;
    }
    if (!root->right)
    {
        struct Node *newRoot = root->left;
        free(root);
        return newRoot;
    }

    // jeœli korzen ma obu synow, to znajdz wezel o najmniejszym kluczu po prawej stronie
    struct Node *successor = root->right;
    while (successor->left) successor = successor->left;
    // zamien wartosc korzenia z najmniejsza wartoscia po prawej stronie
    root->key = successor->key;
    // usun wezel, po prawej stronie, z kopiowana wrtoscia, podajac jako korzen pierwszy wezel po prawej stronie
    root->right = deleteNode(root->right, successor->key);
    return root;
}

// wyswietlanie drzewa
void displayTree(struct Node *root, int level)
{
    //jezli wezel istnieje, to probujemy zejsc nizej
    if (root)
    {
        // najpierw wezel prawy z wieksza wartoscia, dodajemy jeden do numeru poziomu
        displayTree(root->right, level + 1);
        printf("\n");

        //jak z prawej strony wrocimy, to wyswietlamy wartosc naszego wezla poprzedzona odpowiednia iloscia tabulatorow
        for (int i = 0; i < level; i++)
            printf("\t");
        printf("%d", root->key);

        // teraz wezel lewy z mniejsza wartoscia, dodajemy jeden do numeru poziomu
        displayTree(root->left, level + 1);
    }
}

// usuwanie drzewa
struct Node *deleteTree(struct Node *root)
{
    if(root != NULL)
    {
        deleteTree(root->right);
        deleteTree(root->left);
        free(root);
    }
    return NULL;
}

// wyszukiwanie wartosci w drzewie
struct Node *searchNode(struct Node *root, int key)
{
    // ustawienie wezla zawierajacego wartosc podanego klucza na poczatek
    root = splay(root, key);

    // jeœli klucz ju¿ istnieje, to odpowiasdajacy mu wezel bedzie teraz korzeniem
    if (root->key == key)
        printf("\nKlucz %d znajduje sie w drzewie\n", key);
    else
        printf("\nKlucz %d nie znajduje sie w drzewie\n", key);
    return root;
}

// wyswietalnie wszystkich kluczy w kolejnosci rosnacej
void displayInOrder(struct Node *root)
{
    if (root != NULL)
    {

        displayInOrder(root->left);
        printf("%d ", root->key);
        displayInOrder(root->right);
    }
}

// funkcja pomocnicza do pobierania wartosci liczbowej od urzytkowanika
int getNumber()
{
    char decimal = getchar();
    int number = 0;
    do
    {
        number = number * 10 + (int)(decimal - '0');
        decimal = getchar();
    } while (decimal != '\n');
    return number;
}

// MENU dla Splay Tree
// pri - wyswietla cale drzewo
// ord - wyswietla wartosci kluczy w kolejnosci rosnacej
// ins [liczba] - dodaje wezel do drzewa
// del [liczba] - usuwa wezel z drzewa
// scr [liczba] - sprawdza, czy w drzewie jest wartosc
// qui - konczy dzialanie programu
struct Node *askUserForChoice(struct Node *root)
{
    char command[3];
    int parameter;

    while (1)
    {
        printf ("Podaj komende: ");

        command[0] = getchar();
        command[1] = getchar();
        command[2] = getchar();
        char ignore;
        do
        {
            ignore = getchar();
        }
        while(ignore != ' ' && ignore != '\n');


        if (command[0] == 'p' && command[1] == 'r' && command[2] == 'i')
        {
            displayTree(root,0);
            printf("\n");
        }
        else if (command[0] == 'o' && command[1] == 'r' && command[2] == 'd')
        {
            displayInOrder(root);
            printf("\n");
        }
        else if (command[0] == 'i' && command[1] == 'n' && command[2] == 's')
        {
            parameter = getNumber();
            root = insertNode(root,parameter);
        }
        else if (command[0] == 'd' && command[1] == 'e' && command[2] == 'l')
        {
            parameter = getNumber();
            root = deleteNode(root,parameter);
        }
        else if (command[0] == 's' && command[1] == 'r' && command[2] == 'c')
        {
            parameter = getNumber();
            root = searchNode(root,parameter);
        }
        else if (command[0] == 'q' && command[1] == 'u' && command[2] == 'i')
        {
            root = deleteTree(root);
            break;
        }
        else
        {
            fprintf(stderr, "Brak polecenia!\n");
        }
    }
    return root;
}
