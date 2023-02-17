#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


//Create a daemon to change the permissions of a folder to 000 at a specific time every day,
// and to change the permissions to 777 at another time. Eg set to 777 at 9am and set to 000
// at 5pm
int main() {
  // Set the future time
  struct tm future_time;
  future_time.tm_year = 2023 - 1900; // Year - 1900
  future_time.tm_mon = 2 - 1; // Month (January is 0)
  future_time.tm_mday = 18; // Day of the month
  future_time.tm_hour = 9; // Hour (24-hour clock)
  future_time.tm_min = 0; // Minute
  future_time.tm_sec = 0; // Second

  // Convert future_time to a timestamp
  time_t future_timestamp = mktime(&future_time);

  // Get the current time
  time_t now = time(NULL);

  // Calculate the difference between now and the future time
  double seconds = difftime(future_timestamp, now);

  if (seconds < 0) {
    // Future time has already passed
    printf("Future time has already passed!\n");
    return 0;
  }

  // Calculate hours, minutes, and seconds remaining
  int hours = (int) (seconds / 3600);
  int minutes = (int) ((seconds - hours * 3600) / 60);
  int sec = (int) (seconds - hours * 3600 - minutes * 60);

  // Print countdown
  printf("Countdown: %02d:%02d:%02d\n", hours, minutes, sec);

  // Wait for one second
  sleep(1);

  // Create a child process
  pid_t pid = fork();

  if (pid < 0) {
    // Error
    printf("Error creating child process!\n");
    return 1;
  } else if (pid > 0) {
    // Parent process
    printf("Parent process exiting...\n");
    return 0;
  }

  // Child process
  printf("Child process running...\n");

  // Create a new session
  if (setsid() < 0) {
    printf("Error creating new session!\n");
    return 1;
  }

  // Change the current working directory to root
  if (chdir("/") < 0) {
    printf("Error changing working directory!\n");
    return 1;
  }

  // Close standard file descriptors
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  // Run forever until the process is killed
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
    hours = (int) (seconds / 3600);
    minutes = (int) ((seconds - hours * 3600) / 60);
    sec = (int) (seconds - hours * 3600 - minutes * 60);

    // Print countdown
    printf("Countdown: %02d:%02d:%02d\n", hours, minutes, sec);

    // Wait for one second
    sleep(1);
  }

  // Change the permissions of a folder to 000
  if (chmod("/home/username/lab4", 000) < 0) {
    printf("Error changing permissions!\n");
    return 1;
  }

  return 0;
}
