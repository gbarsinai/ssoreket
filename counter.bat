@echo off
setlocal enabledelayedexpansion
	
:::::::::::::::::: COUNTER :::::::::::::::::::::
	IF EXIST ������� (
		cd �������
		for /r %%f in (*) do (				
			set /A Cm=Cm+1
		)
		cd ..
	)
	echo Improved:	!Cm!
	
	IF EXIST ������� (
		cd �������
		IF EXIST "������ ���" (
			cd "������ ���"
			for /r %%f in (*) do (				
				set /A Cad=Cad+1
			)
			cd ..
		)
		echo Albums Glue:	!Cad!
		IF EXIST "������ �����" (
			cd "������ �����"
			for /r %%f in (*) do (				
				set /A Cak=Cak+1
			)
			cd ..
		)
		echo Albums Pockets:	!Cak!
		cd ..
	)
	
	IF EXIST ������ (
		cd ������
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