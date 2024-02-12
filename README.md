# � ���������
|             |                      |
|-------------|----------------------|
| ����������� | ������ �.�.          |
| ���������   | UE 5.3 / c++         |
| ����        | ����� �� 3-�� ����   |
| ��������    | ��������� / �������� |

# ��������

����� �������� ����������� ������ _(��� ������ ���� ��������� �����, �� �����������)_,
������� ����� ��������� �� ������ (`��������`).

### ���� 
������ �����-�� ���������� �������.

### �����������

* ����������� ������
	- �������� � ���������� (`Q`)
* ����������� �����������
	- �������� ��� (`���`)
	- ����� �� ���� (`���`)

��� �������� � ���������� ����� �������� ����������� ����������.

### ������� ���������

����� ����������� � ������ ������ ������ �������� �������� ����.

---

# ����������� ���������

������� ����� ���� �������� �� C++, 
� BluePrint ���������� ��, UI, � ����� ��������� � ������� ��� ������� ��������.

## ����������

���������, ������, ����������� ��������� ������������ �������
��� �����������. ���������� ���� ��������� �������, � ������� ��������,
������ ����������� ��������� ���������� ��������� ���� �������.

��� ������� ���� ���������� ���������� �������������, 
���������, ������������ �������������� ���������. 
��������� �� ���������� ��� ���������

**��������:** �������, 
��������� _MovementOnTheGround_ ����� ���������� ��������� �� �����,
� _MovementFly_ �� �������. 
_MovementComponentInitializer_ ����� � ���� ������� 
����� ���������� �������� �����������.

������ ��������� ����� ������� �����, ������� ���� ��������� 
� �� ������ ������. (_Socium ����������, ���� ����������_)

### InputComponent
������� �� �������� ����������������� �����

### CameraComponent
���������� ������� ������

### MovementComponent
����������� ����� � ����, ������ � �� ���������� �����

### HealthComponent
�������� � ������

### WeaponComponent
���������� ����������� / �������� (��������� ���� �������� �������)

����� �������� �������.

### SociumComponent
��������������� ����� � ����, �� ������������� � ������.

���� ����������� ����� ����� ������� ��������.

## �������

��������� ���������� ���������� ����.

����������� ��� ��������, �� ����� ����� ������ UWorld.

