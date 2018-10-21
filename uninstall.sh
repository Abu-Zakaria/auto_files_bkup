echo "Uninstalling..."
rm /usr/bin/auto_files_bkup

if [ $? -eq 0 ]; then
    echo "Uninstallation completed!"
else
    echo "Uninstallation failed!"
fi
