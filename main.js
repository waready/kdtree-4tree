new Vue({
    el:"main",
    
    data:{
        mensaje:[],
        mane: ""
    
    },
    mounted(){
        this.cargarPersonas();
    },
    methods:{
        cargarPersonas(){
            var url=("http://api-rest-laravel.com.devel/api/post/category/1");
            axios.get(url)
            .then((respuesta) => { 
                
                console.log(respuesta);
                this.mensaje = respuesta.data.posts;
            });
        },
        subir(){
            const params = {

				title: 'perro',  
                content:'nada mas que decir',
                category_id:'1',
                image:'ficticia.png'
				
            };
            var result =JSON.stringify(params);
            

            var result2 =String(result);
            console.log(result2)
            axios({
                method: 'PUT', //{"title":"cast", "content":"Contenido","category_id":"1","image":"ficticia.png"}
                url: 'http://api-rest-laravel.com.devel/api/post/6',
                data: {json:result2},
                headers: {
                  Authorization:"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOjMsImVtYWlsIjoiYW50b255amFwdXJhQGdtYWlsLmNvbSIsIm5hbWUiOiJ0b255Iiwic3VybmFtZSI6InBhcmVkZXMiLCJpYXQiOjE1NzcwNjYwMzgsImV4cCI6MTU3NzY3MDgzOH0.yv3oJaoqsMsrFiFAYyiVuqGD3US7c57DZenVa8JFSHU"
                }
            }).then((respuesta) =>{
                console.log(respuesta)
            });
        }
    },
    computed:{
        searchUser:function(){
          return this.mensaje.filter(item=>item.id.includes(this.name));
        }
      }
});