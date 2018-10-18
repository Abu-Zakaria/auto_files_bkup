echo "Installing..."
cp ./auto_files_bkup /usr/bin

if [ $? -eq 0 ]; then
    echo "Installation completed!"
else
    echo "Installation failed!"
fi
