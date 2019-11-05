@echo off
setlocal enabledelayedexpansion
	
:::::::::::::::::: COUNTER :::::::::::::::::::::
	IF EXIST ™…”˜…š (
		cd ™…”˜…š
		for /r %%f in (*) do (				
			set /A Cm=Cm+1
		)
		cd ..
	)
	echo Improved:	!Cm!
	
	IF EXIST €Œ…‰ (
		cd €Œ…‰
		IF EXIST "€Œ…‰ ƒ—" (
			cd "€Œ…‰ ƒ—"
			for /r %%f in (*) do (				
				set /A Cad=Cad+1
			)
			cd ..
		)
		echo Albums Glue:	!Cad!
		IF EXIST "€Œ…‰ ‹‰‘‰" (
			cd "€Œ…‰ ‹‰‘‰"
			for /r %%f in (*) do (				
				set /A Cak=Cak+1
			)
			cd ..
		)
		echo Albums Pockets:	!Cak!
		cd ..
	)
	
	IF EXIST š”†…˜š (
		cd š”†…˜š
		for /r %%f in (*) do (				
			set /A Ct=Ct+1
		)
		cd ..
	)
	echo Bulk:		!Ct!
	echo -------------------------------
	set /A total=!Cm!+!Cad!+!Cak!+!Ct!
	echo Total: %total%
	
echo Done.
pause