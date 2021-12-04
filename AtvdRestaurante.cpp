#include <iostream>
#include <iomanip>
#include <cstdbool>
using namespace std;

struct Register{
  char meal[30], client[30], waiter[30];// 'meal' = meal name //'waiter' = waiter anme
  int clAge, tableId, waiterId, clId, mealId;//'clAge' = client age// 'tableId' = table identification // 'waiterId' = waiter identification // 'clId' = client identification
  float value; //'value' = meal value
  bool reserved = false; //All tables start 'non reserved' -> 0 = false(non reserved) / 1 = true
};
struct Bill{
  int bookingClId,bookingMeId,bookingTbId;
  float bookingV;
};
bool checkTable(int *num, struct Register *res){
  //table beeing used? false = 0, true = 1
  for(int i=0;i<*num;++i){
    for(int j=i+1;j<*num;++j){
      if(res[i].tableId == res[j].tableId){
        return true;
      }
    }
  }
  return 0;
}
bool checkMeal(int *num, struct Register *res){
  for(int i=0;i<*num;++i){
    for(int j=i+1;j<*num;++j){
      if(res[i].mealId==res[j].mealId){;
        return true;
      }
    }
  }
  return 0;
}
bool checkClient(int *num, struct Register *res){
  for(int i=0;i<*num;++i){
    for(int j=i+1;j<*num;++j){
      if(res[i].clId==res[j].clId){
        return true;
      }
    }
  }
  return 0;
}
bool checkStaff(int *num, struct Register *res){
  for(int i=0;i<*num;++i){
    for(int j=i+1;j<*num;++j){
      if(res[i].waiterId==res[j].waiterId)
      return true;
    }
  }
  return 0;
}
bool reservationClientCheck(struct Register *res,int *clientId,int *contClient){
  for(int i=0;i<*contClient;++i){
    if(*clientId==res[i].clId||*clientId>0){
      return true;
    }
  }
  return 0;
}
bool reservationTableCheck(struct Register *res,int *tableId,int *contTable){
  for(int i=0;i<*contTable;++i){
    if(*tableId==res[i].tableId && res[i].reserved==false){
      return true;
    }
  } 
  return false;
}
bool reservationMealCheck(struct Register *res,int foodId,int contMeal){
  for(int i=0;i<contMeal;++i){
    if(foodId==res[i].mealId){
      return true;
    }
  }
  return 0;
}
void mainMenu(int *op){
  cout<<"\e[1;1H\e[2J";
  cout<<"\n\t========== MENU PRINCIPAL ==========\n";
  cout<<"\n1- Cadastro\n2- Reservas\n3- Relatório\n4- Sair\n";
  cout<<"\n->Selecione uma das opções do menu: ";
  cin>> *op;
  fflush(stdin);
}
void tableRegister(struct Register *res, int *contTable, int num){
  cout<<"\nOpção 'Cadastrar mesa' selecionada...\n";
  cout<< "\nExistem " << *contTable << " mesas cadastradas.\n";
  cout<<"\nQuantas mesas deseja cadastrar: ";
  cin>> num;
  fflush(stdin);
  for(int i=*contTable;i<num;++i){
    cout<<"\n\t->Informe o cód. ID da "<<*contTable+1<<".a mesa: ";
    cin>>res[i].tableId;
    fflush(stdin);
    //checking avalabillity
    if(checkTable(&num,res)!=true){
      cout<<"\nMesa cadastrada com SUCESSO!\n";
      ++*contTable;
      res[i].reserved=false;
    }else{
      cout<<"\n!!Número INVÁLIDO ou Mesa JÁ CADASTRADA!!\n";
      break;//end_adding tables case false
    }
  }
}//end_tableRegister
void mealRegister(struct Register *res, int *contMeal, int num){
  cout<<"\nOpção 'Cadastrar prato' selecionada...\n";
  cout<<"\nExistem " <<*contMeal<< " pratos cadastradas.\n";
  cout<<"\nQuantos pratos deseja cadastrar: ";
  cin>>num;
  for(int i=*contMeal;i<num;++i){
    cout<<"\n\t->Informe o ID do prato: ";
    cin>>res[i].mealId;
    fflush(stdin);
    cout<<"\n\t->Informe o VALOR do prato: ";
    for(int i=*contMeal;i<num;++i){
      cin>>res[i].value;
      fflush(stdin);
      break;
    }
    cout<<"\n\t->Informe o NOME do prato: ";
    cin>>res[i].meal;
    fflush(stdin);
    //checking MealId availabillity
    if(checkMeal(&num, res)==false){
      cout<<"\nPrato cadastrado com SUCESSO\n";
      ++*contMeal;
    }else{
      cout<<"\n!!Código de prato EM USO!!\n";
      break;
    }//end_case Meal true
  }
}
void clientRegister(struct Register *res, int *contClient, int num){
  cout<<"\nOpção 'Cadastrar cliente' selecionada...\n";
  cout<< "\nExistem " << *contClient << " clientes cadastrados.\n";
  cout<<"\nQuantos clientes deseja cadastrar: ";
  cin>> num;
  for(int i=*contClient;i<num;++i){
    cout<<"\t\n->Digite o ID do cliente: ";
    cin>>res[i].clId;
    fflush(stdin);
    cout<<"\t\n->Digite o NOME do cliente: ";
    cin>>res[i].client;
    fflush(stdin);
    cout<<"\t\n->Digite o IDADE do cliente: ";
    cin>>res[i].clAge;
    fflush(stdin);
    if(res[i].clAge < 18){
      cout<<"\n\t>>Bebidas alcoólicas não são permitidas!<<\n";
    }
    //checking Client Id availabillity
    if(checkClient(&num, res)!=true){
      ++*contClient;
      cout<<"\nCliente cadastrado com SUCESSO\n";
    }else{
      cout<<"\n!!ID do cliente em USO ou INVÁLIDO!!\n";
      break;
    }//end_case Client true
  }
}
void staffRegister(struct Register *res, int *contStaff, int num){
  cout<<"\nOpção 'Cadastrar staff' selecionada...\n";
  cout<<"\nExistem " << *contStaff << " garçons cadastrados.\n";
  cout<<"\nQuantos garçons deseja cadastrar: ";
  cin>>num;
  fflush(stdin);
  for(int i=*contStaff;i<num;++i){
    cout<<"\n\t->Informe o ID do staff: ";
    cin>>res[i].waiterId;
    fflush(stdin);
    cout<<"\n\t->Entre com o nome do staff: ";
    cin>>res[i].waiter;
    fflush(stdin);
    //checking Staff ID availability
    if(checkStaff(&num, res)==false){
      ++*contStaff;
      cout<<"Staff cadastrado com SUCESSO";
    }else{
      cout<<"!!Staff JÁ registrado ou número de ID INVÁLIDO!!";
      break;
    }//end_case StaffId true
  }
}
int tableReservation(struct Register *res,int contClient,int contTable,int contMeal, float *overallBill,struct Bill *charge,int *contBook){
  int clientId,tableId,foodId;
  cout<<"\nOpção 'Reserva' selecionada...\n";
  //show clients
  for(int i=0;i<contClient;++i){
    cout<<"\nCliente: "<<res[i].clId<<endl;
  }
  //
  cout<<"\n\t->Informe o ID do cliente: ";
  cin>>clientId;
  fflush(stdin);
  if(reservationClientCheck(res,&clientId,&contClient)==0){
    cout<<"\n!!Cliente NÃO cadastrado ou número de ID INVÁLIDO!!\n";
    return 0;
  }else if(reservationClientCheck(res,&clientId,&contClient)==true){
    cout<<"\e[1;1H\e[2J";
    cout<<"\nCliente identificado...\n";
    charge[*contBook].bookingClId=clientId;
  }
  //Show available tables for reservation
  cout<<"\nID de mesas disponíveis:\n";
  for(int i=0;i<contTable;++i){
    if(res[i].reserved==0){
      cout<<"\n-Mesa: "<<res[i].tableId<<endl;
    }
  }
  cout<<"\n\t->Indique o ID da mesa que deseja reservar: ";
  cin>>tableId;
  fflush(stdin);
  if(reservationTableCheck(res,&tableId,&contTable)==false){
    cout<<"\n!!Mesa RESERVADA ou ID INVÁLIDO!!\n";
      return 0;
  }else if(reservationTableCheck(res,&tableId,&contTable)==true){
    cout<<"\e[1;1H\e[2J";
    charge[*contBook].bookingTbId=tableId;
    for(int i=0;i<contTable;++i){
      if(res[i].tableId==tableId){
        res[i].reserved=true;
        break;
      }
    }
    cout<<"\nMesa reservada COM SUCESSO\n";
    //Meals available
    cout<<"\n\t>>>>> CARDÁPIO <<<<<\n";
    for(int i=0;i<contMeal;++i){
      cout<<"ID: "<<res[i].mealId<<" | Nome: "<<res[i].meal<<" | R$"<<res[i].value<<endl;
    }
    cout<<"\n\t->Informe o ID do prato que deseja: ";
    cin>>foodId;
    fflush(stdin);
    if(reservationMealCheck(res,foodId,contMeal)==false){
      cout<<"!!ID de prato NÃO existe!!";
      for(int i=0;i<contTable;++i){//makes the table available again
        res[i].reserved=false;
      }
      return 0;
    }else if(reservationMealCheck(res,foodId,contMeal)==true){
      charge[*contBook].bookingMeId=foodId;
      for(int i=0;i<contMeal;++i){
        if(foodId==res[i].mealId){
          charge[*contBook].bookingV=res[i].value;
          *overallBill+=charge[*contBook].bookingV;
          break;
        }
      }
      cout<<"\nPrato adicionado com SUCESSO\n";
    }
    ++*contBook;
  }
  return 0;
  }
int freeTable(struct Register *res,struct Bill *charge,int contTable,int contBook){
  int freeTb;
  cout<<"\nOpção 'Liberar reserva' selecionada...\n";
  cout<<"\n->As mesas ocupadas são: \n";
  for(int i=0;i<contTable;++i){
    if(res[i].reserved==true){
      cout<<"\n- Mesa: "<<res[i].tableId<<endl;
    }
  }
  cout<<"\n\t->Indique qual mesa deseja liberar: ";
  cin>>freeTb;
  fflush(stdin);
  for(int i=0;i<contBook;++i){
    if(freeTb==charge[i].bookingTbId){
      cout<<"\nMesa LIBERADA...\n";
      cout<<"\nConta teve valor de: R$"<<charge[i].bookingV<<endl;
      charge[i].bookingTbId=0;
      charge[i].bookingMeId=0;
      charge[i].bookingV=0;
    }
    //Makes table available
    for(int i=0;i<contTable;++i){
      if(freeTb==res[i].tableId){
        res[i].reserved=false;
      }
    }
    //
  }
  return 0;
}
void report(struct Register *res,int contTable,int contMeal,int contClient,int contStaff,float overallBill,int ansReport){
  switch(ansReport){
    case 1:
      cout<<"\e[1;1H\e[2J";
      cout<<"\nOpção 'Exibir todas as mesas' selecionada...\n";
      cout<<"\n\t->Foram cadastradas "<<contTable<<" mesas no total.";
      for(int i=0;i<contTable;++i){
        cout<<"\n->Id de mesa: "<<res[i].tableId<<endl;
      }
      break;//end_show tables
    case 2:
      cout<<"\e[1;1H\e[2J";
      cout<<"\nOpção 'Exibir todos os pratos' selecionada...\n";
      cout<<"\n\t->Foram cadastrados "<<contMeal<<" pratos no total.\n";
      for(int i=0;i<contMeal;++i){
        cout<<"\n->NOME: "<<res[i].meal<<" | ID: "<<res[i].mealId<<endl;
      }
      break;//end_show meals
    case 3:
      cout<<"\e[1;1H\e[2J";
      cout<<"\nOpção 'Exibir todos os clientes' selecionada...\n";
      cout<<"\n\t->Foram cadastrados "<<contClient<<" clientes no total.\n";
      for(int i=0;i<contClient;++i){
        cout<<"\n->NOME: "<<res[i].client<<" | ID: "<<res[i].clId<<" | IDADE: "<<res[i].clAge<<endl;
      }
      break;//end_show clients
    case 4:
      cout<<"\e[1;1H\e[2J";
      cout<<"\nOpção 'Exibir Staff' selecionada...\n";
      cout<<"\n\t->Foram cadastrados "<<contStaff<<" Staff's no total.\n";
      for(int i=0;i<contStaff;++i){
        cout<<"\n->NOME: "<<res[i].waiter<<" | ID: "<<res[i].waiterId<<endl;
      }
      break;//end_show Staff
    case 5:
      cout<<"\e[1;1H\e[2J";
      cout<<"\nOpção 'Exibir receita total' selecionada...\n";
      cout<<"\n\t->A arrecadação total foi de: R$"<<overallBill<<endl;
      break;//end_showBills
    case 6:
      break;
  }
}
int main(){
  struct Register res[50];
  struct Bill charge[50];
  int op,ansRegister,num,contTable=0,contMeal=0,contClient=0,contStaff=0,ansRegisTable,reserveMenu,contBook=0,ansReport;
  float overallBill=0;//total earned
  while(op!=4){
    mainMenu(&op);
    switch(op){
      case 1://register menu
        ansRegisTable=0;
        while(ansRegisTable!=5){
          cout<<"\n\t>>>>>>>>>> MENU CADASTRO <<<<<<<<<<\n";
          cout<<"\n1- Cadastrar mesa\n2- Cadastrar prato\n3- Cadastrar cliente\n4- Cadastrar staff\n5- Voltar ao menu principal\n";
          cout<<"\n\t->Selecione uma das opções do menu acima: ";
          cin>>ansRegister;
          fflush(stdin);
          if(ansRegister==1){
            cout<< "\e[1;1H\e[2J";//clear screen
            tableRegister(res,&contTable,num);
          }else if(ansRegister==2){
            cout<< "\e[1;1H\e[2J";
            mealRegister(res,&contMeal,num);
          }else if(ansRegister==3){
            cout<< "\e[1;1H\e[2J";
            clientRegister(res,&contClient,num);
          }else if(ansRegister==4){
            cout<< "\e[1;1H\e[2J";
            staffRegister(res,&contStaff,num);
          }else if(ansRegister==5){
            break;
          }else{
            cout<<"\nOpção inválida!\n";
          }
        }
        break;//end_register menu
      case 2://reservation
        reserveMenu=0;
        while(reserveMenu!=3){
          cout<<"\n\t>>>>>>>>>> MENU RESERVA <<<<<<<<<<\n";
          cout<<"\n1- Reservar \n2- Liberar reserva (conta)\n3- Voltar ao menu principal\n";
          cout<<"\n\t->Selecione uma das opções do menu acima: ";
          cin>>reserveMenu;
          fflush(stdin);
          if(reserveMenu==1){
            cout<<"\e[1;1H\e[2J";
            tableReservation(res,contClient,contTable,contMeal,&overallBill,charge,&contBook);
          }else if(reserveMenu==2){
            cout<<"\e[1;1H\e[2J";
            freeTable(res,charge,contTable,contBook);
          }else if(reserveMenu==3){
            cout<<"\e[1;1H\e[2J";
          }else{
            cout<<"\nOpção inválida!\n";
          }
        }//end_reserveMenu
      break;//end_reservation
      case 3://report
        ansReport=0;
        cout<<"\e[1;1H\e[2J";
        while(ansReport!=6){
          cout<<"\n\t>>>>>>>>>> MENU EXIBIR <<<<<<<<<<\n";
          cout<<"\n1- Exibir todas as mesas\n2- Exibir todos os pratos\n3- Exibir todos os clientes\n4- Exibir todo o Staff\n5- Exibir receita total\n6- Voltar ao menu relatório\n";
          cout<<"\n-> Selecione uma das opções do menu acima: ";
          cin>>ansReport;
          fflush(stdin);
          report(res,contTable,contMeal,contClient,contStaff,overallBill,ansReport);
        }
      break;//end_report
      case 4:
        cout<< "\e[1;1H\e[2J";
        cout<<"\n\t========== SAINDO... ==========\n";
        break;
    }
  }
  return 0;
}