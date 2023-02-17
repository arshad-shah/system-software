#include <stdio.h>
#include <time.h>

int main() {
  time_t now;
  struct tm future_time;
  double seconds;

  // Set the future time
  future_time.tm_year = 2023 - 1900; // Year - 1900
  future_time.tm_mon = 2 - 1; // Month (January is 0)
  future_time.tm_mday = 17; // Day of the month
  future_time.tm_hour = 9; // Hour (24-hour clock)
  future_time.tm_min = 0; // Minute
  future_time.tm_sec = 0; // Second

  // Convert future_time to a timestamp
  time_t future_timestamp = mktime(&future_time);

  while (1) {
    // Get the current time
    now = time(NULL);

    // Calculate the difference between now and the future time
    seconds = difftime(future_timestamp, now);

    if (seconds < 0) {
      // Future time has already passed
      printf("Future time has already passed!\n");
      break;
    }

    // Calculate hours, minutes, and seconds remaining
    int hours = (int) (seconds / 3600);
    int minutes = (int) ((seconds - hours * 3600) / 60);
    int sec = (int) (seconds - hours * 3600 - minutes * 60);

    // Print countdown
    printf("Countdown: %02d:%02d:%02d\n", hours, minutes, sec);

    // Wait for one second
    sleep(1);
  }

  return 0;
}
