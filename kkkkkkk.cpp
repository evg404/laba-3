#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256]; // �������� ����������
    int priority;  // ��������� �������� (��� ������ �����, ��� ���� ���������)
    struct node* next; // ������ �� ��������� �������
};

// ���������� ��������� ��� ���� ��������
struct node* head_queue = NULL, * last_queue = NULL;    // �������
struct node* head_stack = NULL, * last_stack = NULL;    // ����  
struct node* head_priority = NULL, * last_priority = NULL; // ������������ �������

int dlinna = 0;
char find_el[256];

// �������
struct node* get_struct(void);
void spstore(void);
void spstec(void);
void sppriority(void);
void review_queue(void);
void review_stack(void);
void review_priority(void);
void del_queue(char* name);
void del_stack(char* name);
void del_priority(char* name);
struct node* find_queue(char* name);
struct node* find_stack(char* name);
struct node* find_priority(char* name);
void del_head_queue(void);
void del_head_stack(void);
struct node* dequeue_priority(void);
struct node* peek_priority(void);

// ������� �������� �������� � �����������
struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];
    int priority;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("������ ��� ������������� ������\n");
        exit(1);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("������� �������� �������: ");
    fgets(s, sizeof(s), stdin);

    s[strcspn(s, "\n")] = 0;

    printf("������� ��������� ������� (����� �����): ");
    scanf("%d", &priority);

    if (strlen(s) == 0)
    {
        printf("������ �� ���� �����������\n");
        free(p);
        return NULL;
    }

    strcpy(p->inf, s);
    p->priority = priority;
    p->next = NULL;

    return p;
}

/* ���������� � ������� ������� (� �����) */
void spstore(void)
{
    struct node* p = NULL;

    p = get_struct();
    if (p == NULL)
    {
        return;
    }

    // ���� ������� �����
    if (head_queue == NULL)
    {
        head_queue = p;
        last_queue = p;
    }
    else
    {
        last_queue->next = p;
        last_queue = p;
    }
    printf("������� �������� � ����� �������: %s (��������� %d)\n", p->inf, p->priority);
}

/* ���������� � ���� (� ������) */
void spstec(void)
{
    struct node* p = NULL;

    p = get_struct();
    if (p == NULL)
    {
        return;
    }

    // ���� ���� ����
    if (head_stack == NULL)
    {
        head_stack = p;
        last_stack = p;
    }
    else
    {
        p->next = head_stack;
        head_stack = p;
    }
    printf("������� �������� � ����: %s (��������� %d)\n", p->inf, p->priority);
}

/* ���������� � ������������ ������� (� ����������� �� ����������) */
void sppriority(void)
{
    struct node* p = NULL;
    struct node* current = NULL;
    struct node* prev = NULL;

    p = get_struct();
    if (p == NULL)
    {
        return;
    }

    // ���� ������������ ������� ����� ��� ����� ������� ����� ������ ���������
    if (head_priority == NULL || p->priority > head_priority->priority)
    {
        p->next = head_priority;
        head_priority = p;
        if (last_priority == NULL)
        {
            last_priority = p;
        }
    }
    else
    {
        // ���� ����� ��� �������
        current = head_priority;
        while (current != NULL && current->priority >= p->priority)
        {
            prev = current;
            current = current->next;
        }
        
        // ��������� ����� prev � current
        prev->next = p;
        p->next = current;
        
        // ���� ��������� � �����, ��������� last_priority
        if (current == NULL)
        {
            last_priority = p;
        }
    }
    printf("������� �������� � ������������ �������: %s (��������� %d)\n", p->inf, p->priority);
}

/* �������� ������� ������� */
void review_queue(void)
{
    struct node* struc = head_queue;
    if (head_queue == NULL)
    {
        printf("������� �����\n");
        return;
    }

    printf("���������� �������:\n");
    while (struc)
    {
        printf("��� - %s, ��������� - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

/* �������� ����� */
void review_stack(void)
{
    struct node* struc = head_stack;
    if (head_stack == NULL)
    {
        printf("���� ����\n");
        return;
    }

    printf("���������� �����:\n");
    while (struc)
    {
        printf("��� - %s, ��������� - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

/* �������� ������������ ������� */
void review_priority(void)
{
    struct node* struc = head_priority;
    if (head_priority == NULL)
    {
        printf("������������ ������� �����\n");
        return;
    }

    printf("���������� ������������ �������:\n");
    while (struc)
    {
        printf("��� - %s, ��������� - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

/* ����� � ������� ������� */
struct node* find_queue(char* name)
{
    struct node* struc = head_queue;
    if (head_queue == NULL)
    {
        printf("������� �����\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            return struc;
        }
        struc = struc->next;
    }

    printf("������� �� ������ � �������\n");
    return NULL;
}

/* ����� � ����� */
struct node* find_stack(char* name)
{
    struct node* struc = head_stack;
    if (head_stack == NULL)
    {
        printf("���� ����\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            return struc;
        }
        struc = struc->next;
    }

    printf("������� �� ������ � �����\n");
    return NULL;
}

/* ����� � ������������ ������� */
struct node* find_priority(char* name)
{
    struct node* struc = head_priority;
    if (head_priority == NULL)
    {
        printf("������������ ������� �����\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            return struc;
        }
        struc = struc->next;
    }

    printf("������� �� ������ � ������������ �������\n");
    return NULL;
}

/* �������� �� ������� ������� �� ����� */
void del_queue(char* name)
{
    struct node* struc = head_queue;
    struct node* prev = NULL;
    int flag = 0;

    if (head_queue == NULL)
    {
        printf("������� �����\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head_queue = struc->next;
        if (head_queue == NULL)
        {
            last_queue = NULL;
        }
        free(struc);
        printf("������� ������ �� �������\n");
        return;
    }
    else
    {
        prev = struc;
        struc = struc->next;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            prev->next = struc->next;
            if (struc == last_queue)
            {
                last_queue = prev;
            }
            free(struc);
            printf("������� ������ �� �������\n");
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("������� �� ������ � �������\n");
    }
}

/* �������� �� ����� �� ����� */
void del_stack(char* name)
{
    struct node* struc = head_stack;
    struct node* prev = NULL;
    int flag = 0;

    if (head_stack == NULL)
    {
        printf("���� ����\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head_stack = struc->next;
        if (head_stack == NULL)
        {
            last_stack = NULL;
        }
        free(struc);
        printf("������� ������ �� �����\n");
        return;
    }
    else
    {
        prev = struc;
        struc = struc->next;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            prev->next = struc->next;
            if (struc == last_stack)
            {
                last_stack = prev;
            }
            free(struc);
            printf("������� ������ �� �����\n");
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("������� �� ������ � �����\n");
    }
}

/* �������� �� ������������ ������� �� ����� */
/* �������� �� ������������ ������� �� ����� (��� �������� � ����� ������) */
void del_priority(char* name)
{
    struct node* struc = head_priority;
    struct node* prev = NULL;
    int flag = 0;
    int count = 0;

    if (head_priority == NULL)
    {
        printf("������������ ������� �����\n");
        return;
    }

    // �������� �� ����� ������ � ������� ��� �������� � �������� ������
    while (struc != NULL)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            count++;
            
            // ������� ������� �������
            if (prev == NULL)
            {
                // ������� ������ �������
                head_priority = struc->next;
                if (head_priority == NULL)
                {
                    last_priority = NULL;
                }
                free(struc);
                struc = head_priority;
            }
            else
            {
                // ������� ������� �� �������� ��� �����
                prev->next = struc->next;
                if (struc == last_priority)
                {
                    last_priority = prev;
                }
                free(struc);
                struc = prev->next;
            }
        }
        else
        {
            // ��������� � ���������� ��������
            prev = struc;
            struc = struc->next;
        }
    }

    if (flag == 0)
    {
        printf("�������� � ������ '%s' �� ������� � ������������ �������\n", name);
    }
    else
    {
        printf("������� %d ��������� � ������ '%s' �� ������������ �������\n", count, name);
    }
}

/* �������� ������� �������� �� ������� ������� */
void del_head_queue(void)
{
    if (head_queue == NULL)
    {
        printf("������� �����\n");
        return;
    }
    
    struct node* temp = head_queue;
    head_queue = head_queue->next;
    
    if (head_queue == NULL)
    {
        last_queue = NULL;
    }
    
    printf("������ ������� �� �������: %s (��������� %d)\n", temp->inf, temp->priority);
    free(temp);
}

/* �������� ������� �������� �� ����� */
void del_head_stack(void)
{
    if (head_stack == NULL)
    {
        printf("���� ����\n");
        return;
    }
    
    struct node* temp = head_stack;
    head_stack = head_stack->next;
    
    if (head_stack == NULL)
    {
        last_stack = NULL;
    }
    
    printf("������ ������� �� �����: %s (��������� %d)\n", temp->inf, temp->priority);
    free(temp);
}

/* �������� ������� � ��������� ����������� (��� ��������) */
struct node* peek_priority(void)
{
    return head_priority; // � ������������ ������� ������ ������� ������ � ��������� �����������
}

/* ���������� �������� � ��������� ����������� (� ���������) */
struct node* dequeue_priority(void)
{
    struct node* temp = head_priority;

    if (head_priority == NULL)
    {
        printf("������������ ������� �����\n");
        return NULL;
    }

    head_priority = head_priority->next;
    if (head_priority == NULL)
    {
        last_priority = NULL;
    }

    temp->next = NULL;
    return temp;
}

/* ������� ���� �������� */
void cleanup_all(void)
{
    struct node* temp;
    
    // ������� �������
    while (head_queue != NULL)
    {
        temp = head_queue;
        head_queue = head_queue->next;
        free(temp);
    }
    last_queue = NULL;
    
    // ������� �����
    while (head_stack != NULL)
    {
        temp = head_stack;
        head_stack = head_stack->next;
        free(temp);
    }
    last_stack = NULL;
    
    // ������� ������������ �������
    while (head_priority != NULL)
    {
        temp = head_priority;
        head_priority = head_priority->next;
        free(temp);
    }
    last_priority = NULL;
}

int main()
{
    setlocale(LC_ALL, "rus");

    int choice;
    char name[256];
    struct node* temp;

    while (1)
    {
        printf("\n=== ���� ===\n");
        printf("1. �������� ������� � ������� �������\n");
        printf("2. �������� ������� � ����\n");
        printf("3. �������� ������� � ������������ �������\n");
        printf("4. ����������� ������� �������\n");
        printf("5. ����������� ����\n");
        printf("6. ����������� ������������ �������\n");
        printf("7. ����� ������� � ������� �������\n");
        printf("8. ����� ������� � �����\n");
        printf("9. ����� ������� � ������������ �������\n");
        printf("10. ������� ������� �� ������� ������� �� �����\n");
        printf("11. ������� ������� �� ����� �� �����\n");
        printf("12. ������� ������� �� ������������ ������� �� �����\n");
        printf("13. ������� ������ ������� �� ������� �������\n");
        printf("14. ������� ������ ������� �� �����\n");
        printf("17. �����\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            spstore();
            break;
        case 2:
            spstec();
            break;
        case 3:
            sppriority();
            break;
        case 4:
            review_queue();
            break;
        case 5:
            review_stack();
            break;
        case 6:
            review_priority();
            break;
        case 7:
            printf("������� ��� ��� ������ � �������: ");
            scanf("%s", name);
            temp = find_queue(name);
            if (temp != NULL)
            {
                printf("������ � �������: %s � ����������� %d\n", temp->inf, temp->priority);
            }
            break;
        case 8:
            printf("������� ��� ��� ������ � �����: ");
            scanf("%s", name);
            temp = find_stack(name);
            if (temp != NULL)
            {
                printf("������ � �����: %s � ����������� %d\n", temp->inf, temp->priority);
            }
            break;
        case 9:
            printf("������� ��� ��� ������ � ������������ �������: ");
            scanf("%s", name);
            temp = find_priority(name);
            if (temp != NULL)
            {
                printf("������ � ������������ �������: %s � ����������� %d\n", temp->inf, temp->priority);
            }
            break;
        case 10:
            printf("������� ��� ��� �������� �� �������: ");
            scanf("%s", name);
            del_queue(name);
            break;
        case 11:
            printf("������� ��� ��� �������� �� �����: ");
            scanf("%s", name);
            del_stack(name);
            break;
        case 12:
            printf("������� ��� ��� �������� �� ������������ �������: ");
            scanf("%s", name);
            del_priority(name);
            break;
        case 13:
            del_head_queue();
            break;
        case 14:
            del_head_stack();
            break;
        case 15:
            temp = peek_priority();
            if (temp != NULL)
            {
                printf("������� � ��������� �����������: %s (���������: %d)\n",
                    temp->inf, temp->priority);
            }
            break;
        case 16:
            temp = dequeue_priority();
            if (temp != NULL)
            {
                printf("�������� ������� �� ������������ �������: %s (���������: %d)\n",
                    temp->inf, temp->priority);
                free(temp);
            }
            break;
        case 17:
            cleanup_all();
            printf("������ �������. �����...\n");
            exit(0);
        default:
            printf("�������� �����\n");
        }
    }

    return 0;
}