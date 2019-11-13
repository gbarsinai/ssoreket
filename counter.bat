@echo off
setlocal enabledelayedexpansion
chcp 65001
	
:::::::::::::::::: COUNTER :::::::::::::::::::::
	IF EXIST משופרות (
		cd משופרות
		for /r %%f in (*) do (				
			set /A Cm=Cm+1
		)
		cd ..
	)
	echo Improved:	!Cm!
	
	IF EXIST אלבומים (
		cd אלבומים
		IF EXIST "אלבומי דבק" (
			cd "אלבומי דבק"
			for /r %%f in (*) do (				
				set /A Cad=Cad+1
			)
			cd ..
		)
		echo Albums Glue:	!Cad!
		IF EXIST "אלבומי כיסים" (
			cd "אלבומי כיסים"
			for /r %%f in (*) do (				
				set /A Cak=Cak+1
			)
			cd ..
		)
		echo Albums Pockets:	!Cak!
		cd ..
	)
	
	IF EXIST תפזורת (
		cd תפזורת
		for /r %%f in (*) do (				
			set /A Ct=Ct+1
		)
		cd ..
	)
	echo Bulk:		!Ct!
	
		IF EXIST נגטיבים (
		cd נגטיבים
		for /r %%f in (*) do (				
			set /A Cn=Cn+1
		)
		cd ..
	)
	echo Negativs:	!Cn!
	
		IF EXIST שקופיות (
		cd שקופיות
		for /r %%f in (*) do (				
			set /A Cs=Cs+1
		)
		cd ..
	)
	echo SHKUFIYOT:	!Cs!
	
	echo -------------------------------
	set /A total=!Cm!+!Cad!+!Cak!+!Ct!+!Cn!+!Cs!+0
	echo Total: %total%
	
echo Done.
pause