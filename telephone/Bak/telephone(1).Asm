.386 ;������Ե�αָ���80386���Ժ�Ĵ�������ʹ�ø�ָ�
.model flat, stdcall ;ģʽ����"model �ڴ�ģʽ[,����ģʽ]"
option casemap:none ;ѡ���趨���趨α�Դ�Сд���У�

.code


;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
start:
;������
main proc
	
    push ebp ;����ebp
    mov ebp,esp
    
    call LoadDate
    
CYCLE_MAIN:
    
    ;����
    push offset g_szCls
    call crt_system
    add esp,4
    ;��ʾ�˵�
    call Menu
    ;����g_nChoose
    lea ebx,[g_numScanfFormat]
    mov dword ptr[g_nChoose],0h
    
    push offset g_nChoose ;�������͸�ʽ���Ʒ�
    push ebx
    call crt_scanf
    add esp,8
    
    cmp eax,1
    jnz @T1
    
    ;�˵���ת
    call MenuJump
    
    ;ѭ��
    jmp CYCLE_MAIN
    
@T1:
    call crt_getchar
    cmp eax,0ah
    
    jnz @T1
    
    jmp CYCLE_MAIN
    
MAIN_END:
    mov esp,ebp
    pop ebp	
    
    ret
main endp
end start
end

