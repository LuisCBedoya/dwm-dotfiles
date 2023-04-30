#start dunst
dunst &

#battery notification script 
$HOME/.config/dunst/scripts/low_bat_notifier.sh &

# Set the wallpaper using wal
wal -R &

#picom start
picom &

#start slstatus
slstatus &

#start WM
exec dbus-run-session dwm
