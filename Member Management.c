#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 100

struct Member
{
	int id;
	char name[50];
	char address[50];
	char phone[15];
};

struct Member memberList[MAX_MEMBERS];
int memberCount = 0;

void addMember();
void deleteMember();
void displayMembers();


// this function adds a new member in the list
void addMember()
{
	int i;
	int found = 0;
	struct Member m;

	if(memberCount >= MAX_MEMBERS)
	{
		printf("\nSorry ! Member list is full.\n");
		return;
	}

	printf("\n----- ADD NEW MEMBER -----\n");

	printf("Enter Member ID : ");
	scanf("%d", &m.id);

	// checking if the same id is already used or not
	for(i = 0; i < memberCount; i++)
	{
		if(memberList[i].id == m.id)
		{
			found = 1;
		}
	}

	if(found == 1)
	{
		printf("\nThis ID is already used. Please use another ID.\n");
		return;
	}

	printf("Enter Name : ");
	scanf(" %[^\n]", m.name);

	printf("Enter Address : ");
	scanf(" %[^\n]", m.address);

	printf("Enter Phone Number : ");
	scanf(" %[^\n]", m.phone);

	memberList[memberCount] = m;
	memberCount = memberCount + 1;

	printf("\nMember added successfully !\n");
}


// this function deletes a member using id
void deleteMember()
{
	int i, j, id;
	int pos = -1;

	if(memberCount == 0)
	{
		printf("\nThere is no member to delete.\n");
		return;
	}

	printf("\n----- DELETE MEMBER -----\n");
	printf("Enter Member ID to delete : ");
	scanf("%d", &id);

	// searching the position of that member
	for(i = 0; i < memberCount; i++)
	{
		if(memberList[i].id == id)
		{
			pos = i;
		}
	}

	if(pos == -1)
	{
		printf("\nMember with ID %d is not found.\n", id);
	}
	else
	{
		printf("\nDeleting member : %s\n", memberList[pos].name);

		// shifting all the members one step back
		for(j = pos; j < memberCount - 1; j++)
		{
			memberList[j] = memberList[j + 1];
		}

		memberCount = memberCount - 1;

		printf("Member deleted successfully !\n");
	}
}


// this function shows all the members
void displayMembers()
{
	int i;

	if(memberCount == 0)
	{
		printf("\nNo members are registered yet.\n");
		return;
	}

	printf("\n------------------------- MEMBER LIST -------------------------\n");
	printf("%-8s %-20s %-20s %-15s\n", "ID", "NAME", "ADDRESS", "PHONE");
	printf("---------------------------------------------------------------\n");

	for(i = 0; i < memberCount; i++)
	{
		printf("%-8d %-20s %-20s %-15s\n", memberList[i].id, memberList[i].name, memberList[i].address, memberList[i].phone);
	}

	printf("---------------------------------------------------------------\n");
	printf("Total Members : %d\n", memberCount);
}


/*
	The main() below is only for testing my own part.
	When we join all the parts together, Member 1's menu will
	call these functions, so this main() should be removed.
*/
int main()
{
	int choice;

	while(1)
	{
		printf("\n===== MEMBER MANAGEMENT =====\n");
		printf("1. Add Member\n");
		printf("2. Delete Member\n");
		printf("3. Display Members\n");
		printf("4. Exit\n");
		printf("Enter your choice : ");
		scanf("%d", &choice);

		if(choice == 1)
		{
			addMember();
		}
		else if(choice == 2)
		{
			deleteMember();
		}
		else if(choice == 3)
		{
			displayMembers();
		}
		else if(choice == 4)
		{
			printf("\nExiting...\n");
			break;
		}
		else
		{
			printf("\nWrong choice ! Please try again.\n");
		}
	}

	return 0;
}