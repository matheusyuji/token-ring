#!/bin/bash

machines=()
for i in {1..60}; do
  machines+=("h$i")
done
for i in {1..60}; do
  machines+=("i$i")
done
for i in {1..60}; do
  machines+=("j$i")
done

# Function to run ping command and capture exit code
run_ping() {
  ping -c 1 $1 > /dev/null 2>&1
}

# Array to store PIDs and exit codes
pids=()
exit_codes=()

# Maximum number of concurrent processes
max_processes=10

echo Fazendo ping em ${#machines[@]} máquinas, $max_processes por vez \(isso pode levar alguns instantes\)...

# Run ping commands as child processes
for machine in "${machines[@]}"; do
  # Check the number of running processes
  running=$max_processes;
  while [[ $running -ge $max_processes ]]; do
    running=0
    for pid in "${pids[@]}"; do
      if kill -0 $pid 2>/dev/null; then
        ((running++))
      fi
    done
  done

  run_ping $machine &
  pids+=($!)  # Save the PID of the child process
  echo -n '.'
done

# Wait for all child processes to finish and capture exit codes
for pid in "${pids[@]}"; do
  wait $pid
  exit_codes+=($?)  # Save the exit code of the child process
done

result=""
# Check exit codes and echo machine names for successful pings
for ((i=0; i<${#machines[@]}; i++)); do
  if [ ${exit_codes[i]} -eq 0 ]; then
    result="$result ${machines[i]}"
  fi
done

echo
echo $result