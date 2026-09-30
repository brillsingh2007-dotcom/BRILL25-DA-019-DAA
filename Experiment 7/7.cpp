#include <iostream>
#include <algorithm>
using namespace std;

struct Activity
{
    int start;
    int finish;
    int number;
};

// Sort activities according to finish time
bool compare(Activity a, Activity b)
{
    return a.finish < b.finish;
}

int main()
{
    int n;

    cout << "Enter number of activities: ";
    cin >> n;

    Activity activities[100];

    cout << "Enter start and finish time of each activity:\n";

    for (int i = 0; i < n; i++)
    {
        activities[i].number = i + 1;

        cout << "Activity " << i + 1 << ": ";
        cin >> activities[i].start >> activities[i].finish;
    }

    // Sort activities by finish time
    sort(activities, activities + n, compare);

    cout << "\nSelected Activities:\n";

    // Select the first activity
    int lastFinish = activities[0].finish;

    cout << "Activity " << activities[0].number
         << " (" << activities[0].start
         << ", " << activities[0].finish << ")\n";

    // Select remaining activities
    for (int i = 1; i < n; i++)
    {
        if (activities[i].start >= lastFinish)
        {
            cout << "Activity " << activities[i].number
                 << " (" << activities[i].start
                 << ", " << activities[i].finish << ")\n";

            lastFinish = activities[i].finish;
        }
    }

    return 0;
}
