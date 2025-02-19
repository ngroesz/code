#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct seconds_by_number {
    char phone[12];
    int seconds;
    int cost;
};

struct seconds_by_number parse_seconds_by_number(const char *bill_line)
{
    int parsed_hours = 0, parsed_minutes = 0, parsed_seconds = 0;
    char parsed_phone[12];

    sscanf(bill_line, "%d:%d:%d,%s", &parsed_hours, &parsed_minutes, &parsed_seconds, parsed_phone);

    struct seconds_by_number result;
    strcpy(result.phone, parsed_phone);
    result.seconds =  parsed_hours * (60 * 60) + parsed_minutes * 60 + parsed_seconds;
    return result;
}

int compare_numbers(struct seconds_by_number s_1, struct seconds_by_number s_2)
{
    return strcmp(s_1.phone, s_2.phone);
}

void compute_cost_for_number(struct seconds_by_number *sbn)
{
    if(sbn->seconds < 300) {
        sbn->cost = sbn->seconds * 3;
    } else {
        int minutes = (int) (sbn->seconds / 60);
        if (sbn->seconds % minutes > 0) {
            ++minutes;
        }
        sbn->cost = minutes * 150;
    }
}

void parse_numbers_and_compute_cost(char *text, struct seconds_by_number *parsed_numbers, int *parsed_numbers_size)
{
    char *token;
    char *newline = "\n";
    int line_counter = 0;

    token = strtok(text, newline);
    while (token != NULL) {
        struct seconds_by_number result = parse_seconds_by_number(token);
        struct seconds_by_number *sbn;
        sbn = NULL;
        for(int i = 0; i < *parsed_numbers_size; ++i) {
            if(compare_numbers(parsed_numbers[i], result) == 0) {
                sbn = &parsed_numbers[i];
            }
        }
        if (sbn == NULL) {
            sbn = &parsed_numbers[*parsed_numbers_size];
            (*parsed_numbers_size)++;
            strcpy(sbn->phone, result.phone);
            sbn->seconds = result.seconds;
        } else {
            sbn->seconds += result.seconds;
        }
        token = strtok(NULL, newline);
        ++line_counter;
    }
}

long int phone_number_to_integer(char *number)
{
    long phone_1 = 0, phone_2 = 0, phone_3 = 0;

    sscanf(number, "%ld-%ld-%ld", &phone_1, &phone_2, &phone_3);

    return phone_1 * 1000000000 + phone_2 * 100000 + phone_3;
}

int total_bill(struct seconds_by_number *sbn, int *sbn_size)
{
    struct seconds_by_number *longest_duration = NULL;
    int total_bill = 0;

    for(int i = 0; i < *sbn_size; ++i) {
        if(longest_duration == NULL) {
            longest_duration = &sbn[i];
        } else if(sbn[i].seconds > longest_duration->cost) {
            longest_duration = &sbn[i];
        } else if(phone_number_to_integer(sbn[i].phone) < phone_number_to_integer(longest_duration->phone)) {
            longest_duration = &sbn[i];
        }

        total_bill += sbn[i].cost;
    }

    return total_bill - longest_duration->cost;
}

int solution(char *S)
{
    struct seconds_by_number parsed_numbers[100];
    int parsed_numbers_size = 0;

    parse_numbers_and_compute_cost(S, parsed_numbers, &parsed_numbers_size);

    for(int i = 0; i < parsed_numbers_size; ++i) {
        compute_cost_for_number(&parsed_numbers[i]);
    }

    return total_bill(parsed_numbers, &parsed_numbers_size);
}

int main()
{
    char bill[] = "01:01:01,123-456-789\n00:01:07,400-234-090\n00:05:01,701-080-080\n00:05:00,400-234-090\n00:01:00,123-456-789\n01:02:01,456-789-123\n";
//    char bill[] =  "00:01:07,400-234-090\n00:05:01,701-080-080\n00:05:00,400-234-090";
    printf("solution(): %d\n", solution(bill));

    return 0;
}
