$DRMEM = 'C:/Program Files (x86)/Dr. Memory/bin64/drmemory.exe'
$PROGRAM = '-- ../main.exe'
$LOGDIR = '-logdir S:/drlogs'
$AR = '-light -lib_blocklist_frames 0'
$what = $LOGDIR, $PROGRAM, $AR

Start-Process -FilePath $DRMEM -ArgumentList $what