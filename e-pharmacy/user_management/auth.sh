#!/bin/bash

PROJECT_HOME="."
credentials_file="$PROJECT_HOME/data/credentials.txt"

get_credentials() {
  read -rp "Username: " user
  read -rs -p "Password: " pass
  echo
}

generate_salt() {
  openssl rand -hex 8
  return 0
}

hash_password() {
  local password=$1
  local salt=$2
  echo -n "${password}${salt}" | sha256sum | awk '{print $1}'
  return 0
}

check_existing_username() {
  local username=$1
  local existing_users
  local i
  existing_users=$(cat "$credentials_file")

  for i in ${existing_users}; do
    if [ "$username" == "$(echo "$i" | awk -F ':' '{print $1}')" ]; then
      echo true
      return 0
    fi
  done

  echo false
}

is_role_valid() {
  local roles="normal salesperson admin"
  local role=$1
  local i

  for i in ${roles}; do
    if [ "$role" == "$i" ]; then
      echo true
      return 0
    fi
  done

  echo false
}

register_credentials() {
  local username=$1
  local password=$2
  local fullname=$3
  local role=$4
  local is_logged_in="0"
  local salt
  local hashed_pwd

  if [ "$role" == "" ]; then
    role="normal"
  fi

  if [ "$(check_existing_username "$username")" == "true" ]; then
    echo "Username exists, choose a different username"
    return 1
  fi

  if [ "$(is_role_valid "$role")" == "false" ]; then
    echo "Role not valid, needs to be either of: normal, salesperson, admin"
    return 1
  fi

  salt=$(generate_salt)
  hashed_pwd=$(hash_password "$password" "$salt")

  echo "$username:$hashed_pwd:$salt:$fullname:$role:$is_logged_in" >> $credentials_file
}

verify_credentials() {
  local username=$1
  local password=$2
  local hash
  local salt
  local existing_users
  local user
  local i
  local hashed_pwd
  local user_line_num=0
  existing_users=$(cat "$credentials_file")
  existing_users=${existing_users// /_)))_}

  for i in ${existing_users}; do
    ((user_line_num++))
    if [ "$username" == "$(echo "$i" | awk -F ':' '{print $1}')" ]; then
      hash=$(echo "$i" | awk -F ':' '{print $2}')
      salt=$(echo "$i" | awk -F ':' '{print $3}')
      user=$i
      user=${user//_)))_/ }
      break
    fi
  done

  if [ "$hash" == "" ] || [ "$salt" == "" ]; then
    echo "Invalid username"
    return 1
  fi

  hashed_pwd=$(hash_password "$password" "$salt")

  if [ "$hashed_pwd" == "$hash" ]; then
    local replacement="${user%?}1"
    sed -i "$user_line_num s/.*/$replacement/" $credentials_file
  else
    echo "Invalid password"
    return 1
  fi
}

logout() {
  local existing_users
  local user
  local i
  local user_line_num=0
  existing_users=$(cat "$credentials_file")
  existing_users=${existing_users// /_)))_}

  for i in ${existing_users}; do
    ((user_line_num++))
    if [ "1" == "$(echo "$i" | awk -F ':' '{print $6}')" ]; then
      user=$i
      user=${user//_)))_/ }
      break
    fi
  done

  if [ "$user" == "" ]; then
    return 0
  fi

  local replacement="${user%?}0"
  sed -i "$user_line_num s/.*/$replacement/" $credentials_file
}

delete_credentials() {
  local username=$1
  local existing_users
  local i
  local user_line_num=0
  existing_users=$(cat "$credentials_file")
  existing_users=${existing_users// /_)))_}

  for i in ${existing_users}; do
    ((user_line_num++))
    if [ "$username" == "$(echo "$i" | awk -F ':' '{print $1}')" ]; then
      break
    fi
  done

  sed -i "$user_line_num d" $credentials_file
}

show_log_in() {
  echo "===== Log in ====="
  get_credentials
  verify_credentials "$user" "$pass"
  local is_success=$?

  if [ ! "$is_success" -eq 0 ]; then
    echo "Log in failed!"
    show_menu_to_log_in
    return 0
  fi

  local existing_users
  local i
  existing_users=$(cat "$credentials_file")
  existing_users=${existing_users// /_)))_}

  for i in ${existing_users}; do
    if [ "$user" == "$(echo "$i" | awk -F ':' '{print $1}')" ]; then
      logged_in_user_username="$user"
      logged_in_user_full_name=$(echo "$i" | awk -F ':' '{print $4}')
      logged_in_user_full_name=${logged_in_user_full_name//_)))_/ }
      logged_in_user_role=$(echo "$i" | awk -F ':' '{print $5}')
      break
    fi
  done

  echo "Welcome $fullname! You have successfully logged in as $role."
  show_menu_already_logged_in "$logged_in_user_username" "$logged_in_user_full_name" "$logged_in_user_role"
}

show_register() {
  echo "===== User Registration ====="
  local username
  local password
  local fullname

  read -rp "Username: " username
  read -rs -p "Password: " password
  echo
  read -rp "Enter name: " fullname

  register_credentials "$username" "$password" "$fullname"
  local is_success=$?

  if [ ! "$is_success" -eq 0 ]; then
    echo "User registration failed!"
    show_menu_to_log_in
    return 0
  fi

  echo "Registration successful. You can now log in."
  show_menu_to_log_in
}

show_create_account() {
  echo "===== Create another account ====="
  local username
  local password
  local fullname
  local role

  read -rp "Username: " username
  read -rs -p "Password: " password
  echo
  read -rp "Enter name: " fullname
  read -rp "Enter role (normal, salesperson, admin): " role

  register_credentials "$username" "$password" "$fullname" "$role"
  local is_success=$?

  if [ ! "$is_success" -eq 0 ]; then
    echo "Account creation failed!"
    show_menu_already_logged_in "$logged_in_user_username" "$logged_in_user_full_name" "$logged_in_user_role"
    return 0
  fi

  echo "Account creation successful"
  show_menu_already_logged_in "$logged_in_user_username" "$logged_in_user_full_name" "$logged_in_user_role"
}

show_delete_account() {
  echo "===== Delete an account ====="
  local username

  read -rp "Enter username to delete: " username

  delete_credentials "$username"

  echo "Account for $username successfully deleted"
  show_menu_already_logged_in "$logged_in_user_username" "$logged_in_user_full_name" "$logged_in_user_role"
}

show_menu_to_log_in() {
  local choice

  echo "You're logged out. Select an option:"
  echo "1. Log in"
  echo "2. Register"
  echo "3. Close the program"
  read -rp "Enter your choice: " choice

  case $choice in
  "1")
    show_log_in
    ;;
  "2")
    show_register
    ;;
  "3")
    echo "Exiting ..."
    exit 0
    ;;
  *)
    echo "Invalid choice"
    show_menu_to_log_in
  esac
}

show_menu_already_logged_in() {
  local username=$1
  local fullname=$2
  local role=$3
  local choice

  echo "You're logged in as $fullname, username: $username, role: $role. Choose an option:"

  if [ "$role" == "admin" ]; then
    echo "1. Log out"
    echo "2. Close the program"
    echo "3. Create another account"
    echo "4. Delete an account"
  else
    echo "1. Log out"
    echo "2. Close the program"
  fi


  read -rp "Enter your choice: " choice

  case $choice in
  "1")
    logout
    show_menu_to_log_in
    ;;
  "2")
    echo "Exiting ..."
    exit 0
    ;;
  "3")
    if [ ! "$role" == "admin" ]; then
      echo "Invalid choice"
      show_menu_already_logged_in "$username" "$fullname" "$role"
    else
      show_create_account
    fi
    ;;
  "4")
    if [ ! "$role" == "admin" ]; then
      echo "Invalid choice"
      show_menu_already_logged_in "$username" "$fullname" "$role"
    else
      show_delete_account
    fi
    ;;
  *)
    echo "Invalid choice"
    show_menu_already_logged_in "$username" "$fullname" "$role"
  esac
}

# ==================== Start of program execution ==================== #

if [ ! -f "$credentials_file" ]; then
  touch "$credentials_file"
fi

existing_users=$(cat "$credentials_file")
existing_users=${existing_users// /_)))_}

for i in ${existing_users}; do
  if [ "1" == "$(echo "$i" | awk -F ':' '{print $6}')" ]; then
    logged_in_user=$i
    break
  fi
done

echo "Welcome to the authentication system."

if [ "$logged_in_user" == "" ]; then
  show_menu_to_log_in
else
  logged_in_user_username=$(echo "$i" | awk -F ':' '{print $1}')
  logged_in_user_full_name=$(echo "$i" | awk -F ':' '{print $4}')
  logged_in_user_full_name=${logged_in_user_full_name//_)))_/ }
  logged_in_user_role=$(echo "$i" | awk -F ':' '{print $5}')
  show_menu_already_logged_in "$logged_in_user_username" "$logged_in_user_full_name" "$logged_in_user_role"
fi
